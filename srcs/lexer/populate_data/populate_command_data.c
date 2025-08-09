/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_command_data.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 14:07:43 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:54:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	populate_command_data(t_minishell *minishell, t_lexing *token_list)
{
	t_lexing	*current;
	int			result;

	current = token_list;
	while (current)
	{
		result = handle_redirect(minishell, current);
		if (result == 1)
			return (1);
		else if (result == -1)
			return (-1);
		if (handle_pipe(minishell, current) == -1)
			return (-1);
		if (handle_command(minishell, current) == -1)
			return (-1);
		current = current->next;
	}
	minishell->cmd_current = minishell->cmd_head;
	return (0);
}
