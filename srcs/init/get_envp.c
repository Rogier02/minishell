/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_envp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 17:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/27 16:28:50 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*create_node(char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (new_node == NULL)
		return(NULL);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return(new_node);
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
