/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/24 16:24:18 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/24 16:29:12 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_all_children(t_minishell *minishell)
{
	t_child_p *current;
	
	current = minishell->child;
	while (current)
	{
		if (current->pid > 0)
			kill(current->pid, SIGTERM);
		current = current->next;
	}
}