/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/27 15:36:44 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_up_pipe(t_minishell *minishell)
{
	if (minishell->cmd_current->next)
	{
		if (pipe(minishell->pipe_fd) == -1)
			return (-1);
		redirect_pipes(minishell);
	}
	return (0);
}

static int	clean_up_pipes(t_minishell *minishell, int *previous_read_fd)
{
	if (*previous_read_fd != -1)
	{
		if (close_and_reset_fd(previous_read_fd) == -1)
			return (-1);
	}
	if (minishell->cmd_current->next)
	{
		if (close_and_reset_fd(&minishell->pipe_fd[WRITE_END]) == -1)
			return (-1);
		*previous_read_fd = minishell->pipe_fd[READ_END];
	}
	return (0);
}

static int	run_execution_process(t_minishell *minishell, int *pid)
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
		execute_externals_and_pipes(minishell, pid);
	}
	set_signal_protocal(minishell, execution);
	return (0);
}

int	executor(t_minishell *minishell)
{
	pid_t		pid;
	int			previous_read_fd;
	
	pid = 0;
	previous_read_fd = -1;
	while (minishell->cmd_current)
	{
		if (minishell->cmd_current->cmd)
		{
			if (set_up_pipe(minishell) == -1
				|| run_execution_process(minishell, &pid) == -1
				|| clean_up_pipes(minishell, &previous_read_fd) == -1)
			{
				kill_all_children(minishell);
				wachter(minishell);
				minishell->exit_code = 1;
				return (-1);
			}
		}
		else
			minishell->exit_code = 0;
		minishell->cmd_current = minishell->cmd_current->next;
	}
	wachter(minishell);
	return (0);
}

