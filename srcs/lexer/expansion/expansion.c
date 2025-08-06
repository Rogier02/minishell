/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 18:37:10 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/06 17:09:47 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expan_mini_free(t_expansion *expan)
{
	if (expan->var_name)
		free(expan->var_name);
	if (expan->var_expanded)
		free(expan->var_expanded);
	if (expan)
		free(expan);
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
		if (tilde_expansion(minishell, expan, token, &i) == -1)
			break ;
		else if (expand(minishell, expan, token, &i) == -1)
			return (expan_mini_free(expan), -1);
		if (token->value[i] == '\0')
			continue ;
		i++;
	}
	if (!expan->expanded_input)
		return (expan_mini_free(expan), -1);
	token->expanded_value = expan->expanded_input;
	expan_mini_free(expan);
	return (0);
}

int	expansion(t_minishell *minishell, t_lexing *token)
{
	while(token)
	{
		if (is_redirect_or_pipe(token->type)
			|| (token->previous && token->previous->type == HERE_DOC))
		{
			token->expanded_value = ft_strdup(token->value);
			if (!token->expanded_value)
			{
				ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
				return (-1);
			}
			token = token->next;
			continue ;
		}
		if (expand_token(minishell, token) == -1)
			   return (-1);
		token = token->next;
	}
	return (0);
}
