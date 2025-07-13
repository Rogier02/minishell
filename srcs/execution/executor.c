/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/13 18:42:01 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_execution_process(t_minishell *minishell, int *pid, int *statuscode)
{
	int	result;
	
	if (!minishell->cmd_head->next && check_for_builtins(minishell))
	{
		if (exec_single_builtin(minishell) == -1)
			return (-1); // free
		restore_std(minishell);
		set_signal_protocal(minishell, execution);
		return ;
	}
	if (minishell->cmd_current->next)
	{
		if (pipe(minishell->pipe_fd) == -1)
			return ; // TODO: correct error handling.
		redirect_pipes(minishell);
		execute_externals_and_pipes(minishell, pid);
		// TODO: add child pid to minishell.childs struct
	}
	set_signal_protocal(minishell, execution);
}

int	executor(t_minishell *minishell)
{
	int			wstatus;
	int			statuscode;
	pid_t		pid;
	t_child_p	*last_child_p;

	wstatus = -1;
	statuscode = -1;
	pid = 0;
	last_child_p = NULL;
	
	// TODO: add check for valid data. IE is there cmd data?
	while (minishell->cmd_current)
	{
		if (minishell->cmd_current->cmd)
			run_execution_process(minishell, &pid, &statuscode);
		else
			statuscode = 1;
		minishell->cmd_current = minishell->cmd_current->next;
	}
	if (ret != FAILED_PIPE)
		wait_for_child_proccesses();
	return (exec_cmd(minishell));
}
