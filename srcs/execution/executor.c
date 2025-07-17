/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/16 15:48:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_execution_process(t_minishell *minishell, int *pid, int *statuscode)
{	
	if (!minishell->cmd_head->next && check_for_builtins(minishell))
	{
		if (exec_single_builtin(minishell) == -1)
			return (-1);
		restore_std(minishell);
		set_signal_protocal(minishell, execution);
		return (0);  // Success
	}
	if (minishell->cmd_current->next)
	{
		if (pipe(minishell->pipe_fd) == -1)
			return (-1);
		redirect_pipes(minishell);
		execute_externals_and_pipes(minishell, pid);
	}
	set_signal_protocal(minishell, execution);
	return (0);  // Success
}

int	executor(t_minishell *minishell)
{
	int			statuscode;
	pid_t		pid;
	int			execution_result;

	statuscode = 0;
	pid = 0;
	while (minishell->cmd_current)
	{
		if (minishell->cmd_current->cmd)
		{
			execution_result = run_execution_process(minishell, &pid, &statuscode);
			if (execution_result == -1)
			{
				// Error occurred - set exit code but continue
				minishell->exit_code = 1;
			}
		}
		else
			minishell->exit_code = 1;
		minishell->cmd_current = minishell->cmd_current->next;
	}
	wachter(minishell);
	// Always return to main loop - don't exit shell on command failure
	return (0);
}

