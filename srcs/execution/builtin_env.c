/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 23:03:57 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/08 23:03:57 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_minishell *minishell, char **args)
{
	t_envp	*env;

	if (args && args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	env = minishell->envp;
	while (env)
	{
		if (env->value && ft_strchr(env->value, '='))
		{
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
