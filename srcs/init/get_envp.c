/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_envp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 17:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/06 07:12:57 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return(NULL);
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

void get_envp(t_minishell *minishell, char *envp[])
{
	int	i;
	t_envp *head = NULL;
	t_envp *current = NULL;
	t_envp *previous = NULL;
	
	i = 0;
	head = create_node(envp[i]);
	if (head == NULL)
		error_and_exit("malloc failure\n", minishell);
	i++;
	previous = head;
	while(envp[i])
	{
		current = create_node(envp[i]);
		if (current == NULL)
			error_and_exit("malloc failure_1\n", minishell);
		previous->next = current;
		previous = current;
		i++;
	}
	minishell->envp = head;
}
