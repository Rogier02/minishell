/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_pipes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 16:23:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/13 17:04:34 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipes(t_minishell *minishell)
{
	minishell->cmd_current->outfd = minishell->pipe_fd[WRITE_END];
	minishell->cmd_current->next->infd = minishell->pipe_fd[READ_END];
}