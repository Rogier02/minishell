/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:39:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 21:14:41 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(t_minishell *minishell, int heredoc_fd, char *heredoc_file, t_lexing *token)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n",\
															STDERR_FILENO);
			break;
		}
		if (token->contains_quotes)
			expand_heredoc();
		if (!ft_strncmp(line, token->expanded_value, \
									ft_strlen(token->expanded_value)))
		{
			free(line);
			break;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	create_file_name(t_minishell *minishell, char *heredoc_file, char *temp_file, int heredoc_count)
{
	heredoc_file = ft_strjoin(temp_file, ft_itoa(heredoc_count));
	if (!heredoc_file)
	{
		ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	return (0);
}

static int	clean_up_heredoc(t_minishell *minishell, int heredoc_fd, char *heredoc_file)
{
	close(heredoc_fd);
	unlink(heredoc_fd);
	free(heredoc_file);
	minishell->exit_code = 130;
	return (-1);
}

int	add_heredoc(t_minishell *minishell, char *heredoc_file, int heredoc_fd)
{
	if (minishell->cmd_current->infile->name)
		free(minishell->cmd_current->infile->name);
	minishell->cmd_current->infile->name = ft_strdup(heredoc_file);
	if (!minishell->cmd_current->infile->name)
	{
		close(heredoc_fd);
		unlink(heredoc_fd);
		free(heredoc_file);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_current->infile->type_flag == HERE_DOC;
	close(heredoc_fd);
	unlink(heredoc_fd);
	return (0);
}

int	handle_heredoc(t_minishell *minishell, t_lexing *token)
{
	static int	heredoc_count = 0;
	int			heredoc_fd;
	char		*temp_file;
	char		*heredoc_file;

	temp_file = "/tmp/minishell_heredoc";
	heredoc_file = NULL;
	if (token->previous->type == HERE_DOC)
	{
		heredoc_count += 1;
		if (create_file_name(minishell, heredoc_file, temp_file, heredoc_count) == -1)
			return (-1);
		heredoc_fd = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (heredoc_fd == -1)
			return (free(heredoc_file), -1);
		read_heredoc(minishell, heredoc_fd, heredoc_file, token);
		if (g_heredoc_interrupted == 1)
			return (clean_up_heredoc(minishell, heredoc_fd, heredoc_file));
		if (add_heredoc(minishell, heredoc_file, heredoc_fd) == -1)
			return (-1);
	}
	return (0);
}
