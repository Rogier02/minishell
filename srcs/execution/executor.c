/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/09 16:43:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_builtin(t_minishell *minishell)
{
	char	**cmd;

	cmd = minishell->cmd_head->cmd;
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd), 1);
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(minishell, cmd), 1);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(), 1);
	if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(minishell, cmd), 1);
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(minishell, cmd), 1);
	if (!ft_strncmp(cmd[0], "env", 3))
		return (ft_env(minishell, cmd), 1);
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(minishell, cmd), 1);
	return (0);
}

int	executor(t_minishell *minishell)
{
	if (!minishell->cmd_head 
		|| !minishell->cmd_head->cmd || !minishell->cmd_head->cmd[0])
		return (-1);
	if (run_builtin(minishell))
		return (0);
	int pipe_fd[2];
	pid_t pid; // TODO: might have to put into cmd struct to keep track of children; create struct and add to t_minishell.
	while (minishell->cmd_current)
	{
		if (minishell->cmd_current->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				return (-1); // TODO: assign correct error exit
			minishell->cmd_current->outfd = pipe_fd[WRITE_END]; // TODO: put into funciton. "redire"
			minishell->cmd_current->next->infd = pipe_fd[READ_END];
			if (minishell->cmd_current->outfile)
			{
				close(minishell->cmd_current->outfd);
				minishell->cmd_current->outfd = -1;
			}
		}
		if (minishell->cmd_current->infile && minishell->cmd_current->infd != -1)
		{
			close(minishell->cmd_current->infd);
			minishell->cmd_current->infd = -1;
		}
		// if check for builtin == true.
			// re direct outfile to max fd.
			// 
				// dupe2(STDOUT_FILENO, 1111);
				// dupe2(minishell->cmd_current->outfd, STDOUT_FILENO);
				// dupe2(1111, STDOUT_FILENO);
			//	restore fds
		 	// run_builtin. + esstablish the correct ins and outs. dup2 for output etc.
		// else
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			exec_child(minishell);
		minishell->cmd_current = minishell->cmd_current->next;
		
	}
	// wait for the pids.
	return (exec_cmd(minishell));
}
