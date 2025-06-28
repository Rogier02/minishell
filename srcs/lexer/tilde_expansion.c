/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilde_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 16:41:46 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/28 17:23:56 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_home(t_minishell *minishell, t_expansion *expan)
{
	t_envp	*head;
	char	*home;
	char	*temp;
		
	head = minishell->envp;
	home = expand_home(minishell);
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

int	expand_home_then_pwd(t_minishell *minishell, t_expansion *expan)
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

static int	expand_tilde_home(t_minishell *minishell, t_expansion *expan, t_lexing *token)
{
	if (token->len == 1)
	{
		
	}
	return (0);
}

static int	expand_tilde_short(t_minishell *minishell, t_expansion *expan, t_lexing *token)
{
	if (token->len == 2)
	{
		
	}
	return (0);
}
static int	expand_tilde_special_slash(t_minishell *minishell, t_expansion *expan, t_lexing *token)
{
	if (token->len == 3)
	{
		
	}
	return (0);
}

static int expand_tilde_path(t_minishell *minishell, t_expansion *expan, t_lexing *token)
{
	if (token->len)

}

int	tilde_expansion(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
	if (token->quote_flag == '\0' && token->value[0] == '~')
	{
		if (expand_tilde_home(minishell, expan, token) == -1)
			return (-1);
		if (expand_tilde_short(minishell, expan, token) == -1)
			return (-1);
		if (expand_tilde_special_slash(minishell, expan, token) == -1)
			return (-1);
		if (expand_tilde_path(minishell, expan, token) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
