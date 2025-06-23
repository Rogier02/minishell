/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 18:37:10 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/23 20:18:38 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token(t_minishell *minishell, t_lexing *token)
{
	int	i;
	t_expansion *expan;
	
	expan = ft_calloc(1, sizeof(t_expansion));
	if (!expan)
		return (-1);
	while (token->value[i])
	{
		check_quotes(token->value[i], token->quote_flag);
		if (tilda_expansion(minishell, expan, token))
			break ;
		else if (variable_expansion())
		else if (append_char(minishell, expan, token->value[i]) == -1);
			break ;
		i++;
	}
	free(token->value);
	if (!expan->expanded_input)
		return (-1);
	token->value = expan->expanded_input;
	return (0);
}

int	expansion(t_minishell *minishell, t_lexing *token)
{
	while(token)
	{
		if (is_redirect(token->type))
		{
			token = token->next;
			continue ;
		}
		else if (token->previous && token->previous->type == HERE_DOC)
		{
			token = token->next;
			continue ;
		}
		else if (expand_token(minishell, token) == -1)
			return (-1);
		token = token->next;
	}
}