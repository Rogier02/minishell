/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*    execution.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/21 14:22:22 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/21 15:16:37 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *minishell)
{
	int			wstatus;
	int			exit_status;
	int			pid;
	t_child_p	*previous;

	wstatus = -1;
	exit_status = -1;
	pid = 0;
	while (minishell->cmd_current)
	{
		
	}
	
	// while we have command tables we loop.
	// if the command table has command information filled.
	// 			then we execute the command table. ->
	// else we set that exit code to 1
	//		then the current cmd_table to next.
	
	
}