/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 14:02:40 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 13:03:32 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir(char *input, t_lexing *token)
{
	char	*temp;

	temp = NULL;
	if ((token->type == RE_APPEND || token->type == RE_OUT
			|| token->type == RE_IN || token->type == HERE_DOC)
		&& token->next && token->next->type == WORD)
	{
		temp = ft_substr(input, token->next->start, token->next->len);
		if (!temp)
			return (-1);
		if (!ft_strncmp("\"\"", temp, 2))
			return (free(temp), -1);
		return (free(temp), 0);
	}
	else if ((token->type == RE_APPEND || token->type == RE_OUT
			|| token->type == RE_IN || token->type == HERE_DOC)
		&& token->next && token->next->type != WORD)
	{
		return (-1);
	}
	free(temp);
	return (0);
}

int	syntax_check(char *input, t_lexing *token_list)
{
	t_lexing	*current;

	current = token_list;
	while (current)
	{
		if (check_redir(input, current) == -1)
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return (-1);
		}
		if (current->type == PIPE
			&& (current->previous == NULL || current->next == NULL))
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}
