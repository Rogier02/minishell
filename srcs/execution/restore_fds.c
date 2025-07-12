/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   restore_fds.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 13:49:01 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/12 13:59:14 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdin(t_minishell *minishell)
{
	if (dup2(minishell->original_stdin, STDIN_FILENO) == O_FAILURE)
		error_and_exit("failed to restore original stdin", minishell);
	if (close(minishell->original_stdin) == O_FAILURE)
		error_and_exit("failed to close originall stdin", minishell);
	minishell->original_stdin = -2;	
}

void	restore_stdout(t_minishell *minishell)
{
	if (dup2(minishell->original_stdout, STDOUT_FILENO) == O_FAILURE)
		error_and_exit("failed to restore original stdout", minishell);
	if (close(minishell->original_stdout) == O_FAILURE)
		error_and_exit("failed to close original stdout", minishell);
	minishell->original_stdout = -2;
}

void	restore_fds(t_minishell *minishell)
{
	if (minishell->original_stdin)
		restore_stdin(minishell);
	if (minishell->original_stdout)
		restore_stdout(minishell);
}