/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 18:37:10 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/27 22:19:38 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_dollar_sign(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->quote_flag == '\"' 
		&& (token->value[*i + 1] == '\"' || token->value[*i + 1] == ' '))
	{
		if (append_char(minishell, expan, token->value[*i]) == -1)
		{
			*i += 1;
			return (-1);
		}
	}
	else if (token->len == 1)
	{
		if (append_char(minishell, expan, token->value[*i]) == -1)
		{
			*i += 1;
			return (-1);
		}
	}
	return (0);
}


static int	expand(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->value[*i] == '$' && token->quote_flag != '\'')
	{
		if (only_dollar_sign(minishell, expan, token, i) == -1)
			return (-1);
		else if (append_exit_code(minishell, expan, token, i) == -1)
			return (-1);
		else if (append_variable(minishell, expan, token, i) == -1)
			return (-1);
	}
	return (0);
}

static int	expand_token(t_minishell *minishell, t_lexing *token)
{
	int	i;
	t_expansion *expan;
	
	expan = ft_calloc(1, sizeof(t_expansion));
	if (!expan)
		return (-1);
	expan->envp_copy = minishell->envp;
	i = 0;
	while (token->value[i])
	{
		check_quotes(token->value[i], &token->quote_flag);
		if (tilda_expansion(minishell, expan, token, &i))
			break ;
		else if (expand(minishell, expan, token, &i) == -1)
			return (-1);
		else 
		{
			if (append_char(minishell, expan, token->value[i]) == -1)
			break ;
		}
		i++;
	}
	if (!expan->expanded_input)
		return (-1);
	free(token->value);
	token->value = expan->expanded_input;
	return (0);
}

int	is_redirect(t_token_type type)
{
	if (type == HERE_DOC 
		|| type == RE_APPEND 
		|| type == RE_IN 
		|| type == RE_OUT
		|| type == PIPE)
		return (1);
	return (0);
}

int	expansion(t_minishell *minishell, t_lexing *token)
{
	while(token)
	{
		if (is_redirect(token->type) 
			|| (token->previous && token->previous->type == HERE_DOC))
		{
			token = token->next;
			continue ;
		}
		if (expand_token(minishell, token) == -1)
			   return (-1);
		token = token->next;
	}
	return (0);
}
