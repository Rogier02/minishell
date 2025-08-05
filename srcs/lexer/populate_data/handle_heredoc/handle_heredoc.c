/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:39:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/05 15:50:43 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(t_minishell *minishell, int heredoc_fd, t_lexing *token)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("minishell: heredoc delim by EOF\n", STDERR_FILENO);
			break;
		}
		if (ft_strcmp(line, token->expanded_value) == 0)
		{
			free(line);
			break;
		}
		if (token->contains_quotes == true)
		{
			temp = expand_heredoc(minishell, line);
			if (temp == NULL)
				return (free(line), -1);
			append_line_to_file(heredoc_fd, temp);
			free(temp);
		}
		else
		{
			write(heredoc_fd, line, ft_strlen(line));
			write(heredoc_fd, "\n", 1);
		}
		free(line);
	}
	return (0);
}

static int	create_file_name(t_minishell *minishell, char **heredoc_file, char *temp_file, int heredoc_count)
{
	char *count_str = ft_itoa(heredoc_count);
	if (!count_str)
	{
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	*heredoc_file = ft_strjoin(temp_file, count_str);
	free(count_str);
	if (!*heredoc_file)
	{
		ft_putstr_fd("malloc failure\n", STDERR_FILENO);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	return (0);
}

static int	clean_up_heredoc(t_minishell *minishell, char *heredoc_file)
{
	if (heredoc_file)
	{
		unlink(heredoc_file);
		free(heredoc_file);
	}
	minishell->exit_code = 130;
	return (-1);
}

int	add_heredoc(t_minishell *minishell, char *heredoc_file)
{
	if (minishell->cmd_current->infile->name)
		free(minishell->cmd_current->infile->name);
	minishell->cmd_current->infile->name = ft_strdup(heredoc_file);
	if (!minishell->cmd_current->infile->name)
	{
		unlink(heredoc_file);
		free(heredoc_file);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_current->infile->type_flag = HERE_DOC;
	return (0);
}

int run_heredoc_process(t_minishell *minishell, char *heredoc_file, t_lexing *token)
{	
	pid_t	pid;
	int		status;
	int		heredoc_fd;

	g_heredoc_interrupted = 0;
	heredoc_fd = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc_fd == -1)
	{
		free(heredoc_file);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(heredoc_fd);
		free(heredoc_file);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		read_heredoc(minishell, heredoc_fd, token);
		close(heredoc_fd);
		exit(0);
	}
	//close(heredoc_fd);
	waitpid(pid, &status, 0);
    ft_putstr_fd("Child process finished\n", 2);
    // if (WIFEXITED(status))
    // {
    //     ft_putstr_fd("Child exited normally with code: ", 2);
    //     ft_putnbr_fd(WEXITSTATUS(status), 2);
    //     ft_putstr_fd("\n", 2);
    // }
    // if (WIFSIGNALED(status))
    // {
    //     int received_signal = WTERMSIG(status);
    //     ft_putstr_fd("Child killed by signal: ", 2);
    //     ft_putnbr_fd(received_signal, 2);
    //     ft_putstr_fd(" (SIGINT is ", 2);
    //     ft_putnbr_fd(SIGINT, 2);
    //     ft_putstr_fd(")\n", 2);
        
    //     if (received_signal == SIGINT)
    //     {
    //         ft_putstr_fd("This IS SIGINT\n", 2);
    //     }
    //     else
    //     {
    //         ft_putstr_fd("This is NOT SIGINT\n", 2);
    //     }
    // }
    // if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    // {
    //     ft_putstr_fd("canceled heredoc in parent\n", 2);
    //     ft_putstr_fd("canceled heredoc in parent\n", 2);
    //     unlink(heredoc_file);
    //     free(heredoc_file);
    //     close(heredoc_fd);
    //     minishell->exit_code = 130;
    //     return (-2);
    // }
    // Also check if child exited with 130
   	if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
    {
        ft_putstr_fd("heredoc interrupted (exit 130)\n", 2);
        unlink(heredoc_file);
        free(heredoc_file);
        close(heredoc_fd);
        minishell->exit_code = 130;
        return (-2);
    }
	return (0);
}

int	handle_heredoc(t_minishell *minishell, t_lexing *token)
{
	static int	heredoc_count = 0;
	int			res;
	char		*temp_file;
	char		*heredoc_file;

	temp_file = "/tmp/minishell_heredoc";
	heredoc_file = NULL;
	g_heredoc_interrupted = 0;
	if (token->previous->type == HERE_DOC)
	{
		heredoc_count += 1;
		if (create_file_name(minishell, &heredoc_file, temp_file, heredoc_count) == -1)
			return (-1);
		res = run_heredoc_process(minishell, heredoc_file, token);
		if (res == -2)
			return (-2);
		set_signal_protocal(minishell, main_shell);
		if (g_heredoc_interrupted == 1)
			return (clean_up_heredoc(minishell, heredoc_file));
		if (add_heredoc(minishell, heredoc_file) == -1)
			return (-1);
		free(heredoc_file);
	}
	return (0);
}

