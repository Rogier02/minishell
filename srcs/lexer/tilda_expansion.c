/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilda_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 16:41:46 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/25 19:36:24 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_home(t_minishell *minishell, t_expansion *expan)
{
	t_envp	*head;
	char	*home;
	char	*temp;
		
	head = minishell->envp;
	home = get_home(minishell->envp);
	if (!home)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, home);
	if (!temp)
	{
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure \n", STDERR_FILENO);
		return (free(home), -1);
	}
	free(expan->expanded_input);
	expan->expanded_input = temp;
	return (0);
}

static int	expand_home_then_pwd(t_minishell *minishell, t_expansion *expan)
{
	char	*pwd;
	char	*temp;
	
	if (append_home(minishell, expan) == -1)
		return (-1);
	pwd = expand_pwd(minishell);
	if (!pwd)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, pwd);
	if (!temp)
	{
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure: \n", STDERR_FILENO);
		return (free(pwd), -1);
	}
	free(expan->expanded_input);
	expan->expanded_input = temp;
	return (0);	
}

static int	expand_home_then_oldpwd(t_minishell *minishell, t_expansion *expan)
{	
	char	*oldpwd;
	char	*temp;
	
	if (append_home(minishell, expan) == -1)
		return (-1);
	oldpwd = expand_oldpwd(minishell);
	if (!oldpwd)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, oldpwd);
	if (!temp)
	{
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure: \n", STDERR_FILENO);
		return (free(oldpwd), -1);
	}
	free(oldpwd);
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
			if (expand_home_then_pwd(minishell, expan) == -1)
				return (-1);
		}
		else if (token->value[*i + 1] == '-' 
			&& (token->value[*i + 2] == '/' || token->value[*i + 1] == '\0'))
		{
			if (expand_home_then_oldpwd(minishell, expan) == -1)
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
