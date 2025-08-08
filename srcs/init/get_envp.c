/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_envp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 17:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 18:07:01 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envp(t_envp *envp)
{
	t_envp	*current;
	t_envp	*next;

	current = envp;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static void	set_empty_node(t_envp *new_node, char *env)
{
	new_node->key = ft_strdup(env);
	new_node->value = ft_strdup("");
}

static t_envp	*create_node(char *env)
{
	t_envp	*new_node;
	char	*equal_sign;
	size_t	key_len;

	new_node = malloc(sizeof(t_envp));
	if (new_node == NULL)
		return (NULL);
	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		set_empty_node(new_node, env);
	else
	{
		key_len = equal_sign - env;
		new_node->key = malloc(key_len + 1);
		if (!new_node->key)
		{
			free(new_node);
			return (NULL);
		}
		ft_strlcpy(new_node->key, env, key_len + 1);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	new_node->next = NULL;
	return (new_node);
}

static t_envp	*build_envp_list(char *envp[])
{
	int		i;
	t_envp	*head;
	t_envp	*current;
	t_envp	*previous;

	i = 0;
	head = create_node(envp[i]);
	if (head == NULL)
		return (NULL);
	i++;
	previous = head;
	while (envp[i])
	{
		current = create_node(envp[i]);
		if (current == NULL)
		{
			free_envp(head);
			return (NULL);
		}
		previous->next = current;
		previous = current;
		i++;
	}
	return (head);
}

void	get_envp(t_minishell *minishell, char *envp[])
{
	if (envp == NULL || envp[0] == NULL)
	{
		minishell->envp = NULL;
		return ;
	}
	minishell->envp = build_envp_list(envp);
	if (minishell->envp == NULL)
		error_and_exit("malloc failure\n", minishell);
}
