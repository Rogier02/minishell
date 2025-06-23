/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 19:49:24 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/23 19:49:24 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_envp **env, t_envp **prev, t_envp **curr)
{
	t_envp	*tmp;

	tmp = *curr;
	if (*prev)
		(*prev)->next = (*curr)->next;
	else
		*env = (*curr)->next;
	*curr = (*curr)->next;
	free(tmp->value);
	free(tmp);
}

static void	mini_remove_env(char *str, t_envp **env)
{
	t_envp	*prev;
	t_envp	*curr;
	size_t	len;

	prev = NULL;
	curr = *env;
	len = ft_strlen(str);
	while (curr)
	{
		if (ft_strncmp(curr->value, str, len) == 0 && curr->value[len] == '=')
			remove_env_node(env, &prev, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int	builtin_unset(t_minishell *minishell, char **args)
{
	int		i;
	t_envp	*env;

	i = 1;
	env = minishell->envp;
	while (args[i])
	{
		mini_remove_env(args[i], &env);
		i++;
	}
	return (0);
}
