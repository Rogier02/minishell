/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expansion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 15:46:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:30:51 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_expansion	*init_expan_heredoc(t_minishell *minishell)
{
	t_expansion	*expan;

	expan = ft_calloc(1, sizeof(t_expansion));
	if (!expan)
		return (NULL);
	expan->envp_copy = minishell->envp;
	expan->expanded_input = ft_strdup("");
	return (expan);
}

static int	handle_heredoc_expansion(t_minishell *minishell,\
						t_expansion *expan, char *line, int *i)
{
	if (line[*i + 1] == '?')
	{
		if (heredoc_append_exit_code(minishell, expan, line, i) == -1)
		{
			minishell->exit_code = ENOMEM;
			return (-1);
		}
	}
	else if (ft_isalpha(line[*i + 1]) || line[*i + 1] == '_')
	{
		if (heredoc_append_variable(minishell, expan, line, i) == -1)
		{
			minishell->exit_code = ENOMEM;
			return (-1);
		}
	}
	return (0);
}

char	*expand_heredoc(t_minishell *minishell, char *line)
{
	t_expansion	*expan;
	char		*res;
	int			i;

	expan = init_expan_heredoc(minishell);
	if (!expan)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (handle_heredoc_expansion(minishell, expan, line, &i) == -1)
				return (free_expansion(expan), NULL);
			continue ;
		}
		else if (heredoc_append_char(minishell, expan, line[i]) == -1)
			return (free_expansion(expan), NULL);
		i++;
	}
	res = ft_strdup(expan->expanded_input);
	free_expansion(expan);
	if (!res)
		return (NULL);
	return (res);
}
