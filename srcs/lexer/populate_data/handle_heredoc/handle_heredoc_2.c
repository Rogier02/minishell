/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 12:31:49 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:33:18 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_line(t_minishell *minishell, int heredoc_fd, \
	t_lexing *token, char *line)
{
	char	*temp;

	if (token->contains_quotes == true)
	{
		temp = expand_heredoc(minishell, line);
		if (temp == NULL)
			return (-1);
		append_line_to_file(heredoc_fd, temp);
		free(temp);
	}
	else
	{
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
	}
	return (0);
}

static int	check_heredoc_delimiter(char *line, t_lexing *token)
{
	if (ft_strcmp(line, token->expanded_value) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	read_heredoc(t_minishell *minishell, int heredoc_fd, t_lexing *token)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("minishell: heredoc delim by EOF\n", STDERR_FILENO);
			break ;
		}
		if (check_heredoc_delimiter(line, token))
			break ;
		if (process_heredoc_line(minishell, heredoc_fd, token, line) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	create_file_name(t_minishell *minishell, char **heredoc_file,\
	char *temp_file, int heredoc_count)
{
	char	*count_str;

	count_str = ft_itoa(heredoc_count);
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

int	clean_up_heredoc(t_minishell *minishell, char *heredoc_file)
{
	if (heredoc_file)
	{
		unlink(heredoc_file);
		free(heredoc_file);
	}
	minishell->exit_code = 130;
	return (-1);
}
