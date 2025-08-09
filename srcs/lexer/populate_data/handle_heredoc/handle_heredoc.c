/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:39:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:47:43 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_heredoc_child(t_minishell *minishell,\
	int heredoc_fd, t_lexing *token)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	read_heredoc(minishell, heredoc_fd, token);
	close(heredoc_fd);
	exit(0);
}

static int	handle_heredoc_parent(t_minishell *minishell,\
	char *heredoc_file, int heredoc_fd, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status)
			&& (WTERMSIG(status) == SIGINT
				|| WTERMSIG(status) == 120)))
	{
		ft_putstr_fd("canceled heredoc in parent\n", 2);
		ft_putstr_fd("canceled heredoc in parent\n", 2);
		unlink(heredoc_file);
		free(heredoc_file);
		close(heredoc_fd);
		minishell->exit_code = 130;
		return (-2);
	}
	return (0);
}

int	run_heredoc_process(t_minishell *minishell,\
	char *heredoc_file, t_lexing *token)
{
	pid_t	pid;
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
		handle_heredoc_child(minishell, heredoc_fd, token);
	return (handle_heredoc_parent(minishell, heredoc_file, heredoc_fd, pid));
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
		if (create_file_name(minishell, \
&heredoc_file, temp_file, heredoc_count) == -1)
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
