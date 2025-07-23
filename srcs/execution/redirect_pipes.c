/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_pipes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 16:23:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/23 19:56:43 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: fix this redirect. 
	// pipe references are lost if an outfile overrides the pipe.
	// either check where the out/infile is opened and close the pipefd before overriding or handle it here
void	redirect_pipes(t_minishell *minishell, int *pipefd)
{
	if (minishell->cmd_current->next)
	{
		minishell->cmd_current->outfd = pipe_fd[WRITE_END];
		minishell->cmd_current->next->infd = pipe_fd[READ_END];
	}
	if (minishell->cmd_current != minishell->cmd_head)
	{
		if (close(minishell->pipe_fd[READ_END]) == -1)
			error_and_exit("minishell: close failure\n", minishell);
	}
	if (!minishell->cmd_current->next)
	{
		if (close(minishell->pipe_fd[WRITE_END]) == -1)
			error_and_exit("minishell: close failure\n", minishell);
	}
	if (minishell->cmd_current->next 
		&& minishell->cmd_current->next->infile)
	{
		if (close(pipefd()))
	}
}