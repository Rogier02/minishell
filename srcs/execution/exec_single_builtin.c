/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_single_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/11 18:50:52 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/12 19:55:12 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_dup_infile(t_minishell *minishell)
{
	if (open(minishell->cmd_current->infile->name, st))
}

static int	handle_redirects_for_parent_process(t_minishell *minishell)
{
	if (minishell->cmd_current->outfile)
	{
		minishell->original_stdout = dup(STDOUT_FILENO);
		if (minishell->original_stdout == -1)
			return (set_error_and_print("failed to dup stdout\n", minishell)); // TODO: should not exit. inside the parent process it should return.
		if (open_outfile(minishell) == -1)
			return (-1); // TODO: setup error function.
	}
	if (minishell->cmd_current->infile)
	{
		minishell->original_stdin = dup(STDIN_FILENO);
		if(minishell->original_stdin == -1)
			return (set_error_and_print("failed to dupe stdin\n", minishell));
		if (open_and_dup_infile(minishell) == -1)
			return (-1);
	}
	return (0);
}

int	exec_single_builtin(t_minishell *minishell)
{
	
	if (handle_redirects_(minishell) == -1);
		return (-1);
	if (execute_builtin(minishell) == -1);
		return (-1);
	return (0);
}