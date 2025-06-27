/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_pwd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 19:26:43 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/27 15:44:18 by rgoossen      ########   odam.nl         */
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