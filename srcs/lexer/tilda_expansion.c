/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilda_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 16:41:46 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/25 17:58:22 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_home(t_envp *envp, t_expansion *expan)
{
	t_envp	*head;
	char	*home;
	char	*temp;
		
	head = envp;
	home = get_home();
	temp = ft_strjoin(expan->expanded_input, home);
	if (!temp)
		return (free(home), -1);
	free(expan->expanded_input);
	expan->expanded_input = temp;
	return (0);
}

int	tilda_expansion(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->value[*i] == '~' 
		&& token->quote_flag == '\0' && *i == 0)
	{
		if (token->value[*i + 1] == '+' 
			&& (token->value[*i + 2] == '/' || token->value[*i + 1] == '\0'))
		{
			if (expand_home_then_pwd() == -1)
				return (-1);
		}
		else if (token->value[*i + 1] == '-' 
			&& (token->value[*i + 2] == '/' || token->value[*i + 1] == '\0'))
		{
			if (expand_home_then_oldpwd() == -1)
				return (-1);
		}
		else if (token->value[*i + 1] == '/' || token->value[*i + 1] == '\0')
		{
			if (expand_home() == -1)
				return (-1);
		}
	}
	return (0);
}
