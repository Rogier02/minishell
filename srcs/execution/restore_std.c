/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   restore_std.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 13:49:01 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/07 12:25:49 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_stdin(t_minishell *minishell)
{
	if (dup2(minishell->original_stdin, STDIN_FILENO) == -1)
		return (perror("failed to close originall stdin"), -1);
	if (close(minishell->original_stdin) == -1)
		return (perror("failed to close originall stdin"), -1);
	minishell->original_stdin = -2;	
	return (0);
}

static int	restore_stdout(t_minishell *minishell)
{
	if (dup2(minishell->original_stdout, STDOUT_FILENO) == -1)
		return (perror("failed to restore original stdout"), -1);
	if (close(minishell->original_stdout) == -1)
		return (perror("failed to close original stdout"), -1);
	minishell->original_stdout = -2;
	return (0);
}

int	restore_std(t_minishell *minishell)
{
	if (minishell->original_stdin >= 0)
	{
		if (restore_stdin(minishell) == -1)
			return (-1);
	}
	if (minishell->original_stdout >= 0)
	{
		if (restore_stdout(minishell) == -1)
			return (-1);
	}
	return (0);
}