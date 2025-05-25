/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/25 20:18:35 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/25 20:49:58 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredoc_input(t_parsing *p, int heredoc_fd, char *delimiter)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line) // should handle with signals TODO: double check
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", STDERR_FILENO);
			break;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
}

int handle_heredoc(t_parsing *p, char *delimiter)
{
	int		heredoc_fd;

	heredoc_fd = open(p->temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc_fd == -1)
	{
		p->parser_error = "minishell: heredoc";
		return (-1);
	}
	get_heredoc_input(p, heredoc_fd, delimiter);
	close(heredoc_fd);
	if (p->cmd_table->infile)
		free(p->cmd_table->infile);
	p->cmd_table->infile = ft_strdup(p->temp_file);
	if (!p->cmd_table->infile)
	{
		p->parser_error = "malloc failure: ";
		return (-1);
	}
	return (0);
}