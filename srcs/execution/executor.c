/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/23 19:50:10 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_execution_process(t_minishell *minishell, int *pid, int *pipefd)
{	
	if (!minishell->cmd_head->next && check_for_builtins(minishell))
	{
		if (exec_single_builtin(minishell) == -1)
			return (-1);
		restore_std(minishell);
		set_signal_protocal(minishell, execution);
		return (0);
	}
	else
	{
		if (minishell->cmd_current->next && pipe(pipefd) == -1)
		{
			if (pipe(pipefd) == -1)
				return (-1);
			redirect_pipes(minishell, pipefd);
		}
		execute_externals_and_pipes(minishell, pid);
	}
	set_signal_protocal(minishell, execution);
	return (0);
}

int	executor(t_minishell *minishell)
{
	pid_t		pid;
	int			execution_result;
	int			*pipefd[2];

	pid = 0;
	while (minishell->cmd_current)
	{
		if (minishell->cmd_current->cmd)
		{
			execution_result = run_execution_process(minishell, &pid, pipefd);
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

