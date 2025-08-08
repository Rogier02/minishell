/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_pipes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 16:23:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 14:58:55 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_pipes(t_minishell *minishell)
{
	minishell->cmd_current->outfd = minishell->pipe_fd[WRITE_END];
	if (minishell->cmd_current->next)
	{
		minishell->cmd_current->next->infd = minishell->pipe_fd[READ_END];
	}
}
