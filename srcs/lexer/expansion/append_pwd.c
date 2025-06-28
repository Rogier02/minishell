/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_pwd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 19:26:43 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/28 18:41:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_pwd(t_minishell *minishell)
{
	char	*pwd;

	pwd = ft_strdup(minishell->pwd);
	if (!pwd)
	{
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure \n", STDERR_FILENO);
		return (NULL);
	}
	return (pwd);
}

char	*expand_oldpwd(t_minishell *minishell)
{
	t_envp	*head;
	char	*oldpwd;

	head = minishell->envp;
	while (head)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 7))
		{
			oldpwd = ft_strdup(head->value + 7);
			if (oldpwd == NULL)
			{
				minishell->exit_code = ENOMEM;
				error_and_exit("malloc failure\n", minishell);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (oldpwd);
}
int	append_pwd(t_minishell *minishell, t_expansion *expan)
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

int	append_oldpwd(t_minishell *minishell, t_expansion *expan)
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