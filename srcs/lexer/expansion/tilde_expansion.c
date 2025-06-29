/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilde_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 16:41:46 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 12:40:16 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_tilde_home(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->len == 1)
	{
		(*i) += 1;
		if (append_home(minishell, expan) == -1)
			return (-1);
	}
	return (0);
}

static int	expand_tilde_short(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->len == 2)
	{
		if (!ft_strncmp("~+", token->value, 2))
		{
			(*i) += 2;
			if (append_pwd(minishell, expan) == -1)
				return (-1); 
		}
		if (!ft_strncmp("~-", token->value, 2))
		{
			(*i) += 2;
			if (append_oldpwd(minishell, expan) == -1)
				return (-1);
		}
		if (!ft_strncmp("~/", token->value, 2))
		{
			(*i) += 1;
			if (append_home(minishell, expan) == -1)
				return (-1);
		}
		return (1);
	}
	return (0);
}
// static int	expand_tilde_special_slash(t_minishell *minishell, t_expansion *expan, t_lexing *token)
// {
	
// }

static int expand_tilde_path(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->len >= 3)
	{
		if (!ft_strncmp("~+/", token->value, 3))
		{	
			(*i) += 2;
			if (append_pwd(minishell, expan) == -1)
				return (-1);
		}
		if (!ft_strncmp("~-/", token->value, 3))
		{
			(*i) += 2;
			if (append_oldpwd(minishell, expan) == -1)
				return (-1);
		}
	}
	return (0);
}

int	tilde_expansion(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->quote_flag == '\0' && token->value[*i] == '~')
	{
		if (expand_tilde_home(minishell, expan, token, i) == -1)
			return (-1);
		if (expand_tilde_short(minishell, expan, token, i) == -1)
			return (-1);
		if (expand_tilde_path(minishell, expan, token, i) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
