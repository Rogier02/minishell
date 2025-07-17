/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_single_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/11 18:50:52 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/16 13:14:21 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int collect_original_fds(t_minishell *minishell)
{
	minishell->original_stdin = dup(STDIN_FILENO);
	if (minishell->original_stdin == -1)
		return (perror("failed to dup original stdin"), -1);
	minishell->original_stdout = dup(STDOUT_FILENO);
	if (minishell->original_stdout == -1)
		return (perror("failed to dup original stdout"), -1);
	return (0);
}

static int	open_files_to_fds(t_minishell *minishell)
{
	if (open_infile(minishell) == -1)
		return (-1);
	if (open_outfile(minishell) == -1)
		return (-1);
	return (0);
}

static int redirect_fds(t_minishell *minishell)
{
	if (minishell->cmd_current->infd != -1)
	{
		if (dup2(minishell->cmd_current->infd, STDIN_FILENO) == -1)
			return (perror("failed to dup infd to STDIN"), -1);
	}
	if (minishell->cmd_current->outfd != -1)
	{
		if (dup2(minishell->cmd_current->outfd, STDOUT_FILENO) == -1)
			return (perror("failed to dup outfd to STDOUT"), -1);
	}
	return (0);
}

int	exec_single_builtin(t_minishell *minishell)
{
	if (collect_original_fds(minishell) == -1)
		return (-1);
	if (open_files_to_fds(minishell) == -1);
		return (-1);
	if (redirect_fds(minishell) == -1)
		return (-1);
	if (exec_builtin(minishell) == -1);
		return (-1);
	return (0);
}