/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 12:22:17 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 12:22:20 by rgoossen      ########   odam.nl         */
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
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
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
		if (!ft_strncmp(curr->key, str, len))
		{
			remove_env_node(env, &prev, &curr);
			return ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int		i;
	t_envp	*env;

	i = 1;
	env = minishell->envp;
	if (!args[1])
		return (0);
	while (args[i])
	{
		mini_remove_env(args[i], &env);
		i++;
	}
	return (0);
}
