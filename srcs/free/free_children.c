/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 17:36:17 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 15:02:51 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recess(t_child_p *child)
{
	t_child_p	*next;

	while (child)
	{
		next = child->next;
		free(child);
		child = next;
	}
}
