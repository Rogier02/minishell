/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wachter.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 12:12:20 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 12:30:24 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wachter(t_minishell *minishell)
{
	t_child_p	*current;
	int			status;

	current = minishell->child;
	status = 0;
	while (current)
	{
		if (current->pid > 0)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status))
				minishell->exit_code = WEXITSTATUS(status);
		}
		current = current->next;
	}
}
