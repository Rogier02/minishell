/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_pipes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 16:23:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/25 15:35:16 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: fix this redirect. 
	// pipe references are lost if an outfile overrides the pipe.
	// either check where the out/infile is opened and close the pipefd before overriding or handle it here
void	redirect_pipes(t_minishell *minishell)
{
	minishell->cmd_current->outfd = minishell->pipe_fd[WRITE_END];
	if (minishell->cmd_current->next)
	{
		minishell->cmd_current->next->infd = minishell->pipe_fd[READ_END];
	}
}