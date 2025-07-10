/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/10 15:55:21 by rgoossen      ########   odam.nl         */
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

void	run_execution_process(t_minishell *minishell, pid_t *pid, int *statuscode)
{
	if (minishell->cmd_current->next)
	{
		if (pipe(minishell->cmd_current->next->pipe_fd) == -1)
			return ; // TODO: correct error handling.		
	}
	// if there is no next cmd struct/pipe and cmd_current is equal to cmd_head.
		// check for and execute builtins.
			// run_builtins(); < needs a check for builtins.
		// restore fds if need be. 
			// if (minishell.original_stdin has been changed. IE is greater than 0
				// restore original_stdin to the STDIN_FILENO
					// check for dup failure ^
				// close original_stdin
					//check for close failure ^
				// set original_stdin to -2
			// if (minishell.original_stdout has been changed. IE is greater than 0)
				// restore original_stdout to the STDOUT_FILENO
					//check for dup failure ^
				// close original_stdin
					//check for close failure ^
				// set original_stdout to -2
	
	// if the given command is not a builtin and there is a pipe (cmd_table.next). 
		// the program should fork. 
			// check for fork failure.
		// if the pid == 0
			// handle redirects
				// check if there are outfiles or infiles.
					// if there are available files. then open the files. 
					// dupe the files to the in and out fds.
					// close the appropriate fds after duping.
			// if  current_cmd != cmd
				// dupe the read
					// if pipe_fd[READ] exits and infd is less than 1
						// if dup2(pipe_fd[READ], STDIN_FILENO) == -1
							//handle_error.
					// if pipe_fd[READ] 
						// if close(pipe_fd[READ] == -1)
							// handle error
			// if there is a pipe
				// dupe the write.
					// if pipe_fd[WRITE] exits and outfd is less than 1
						// if dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1
							//handle_error.
					// if pipe_fd[WRITE] 
						// if close(pipe_fd[WRITE] == -1)
							// handle error
							
			// run child process to execute commands.
				// check builtin fds?
				
		// run command through execve.
	// re-initialize signals to regulare execution layer.
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
	}
	wait_for_child_proccesses();
	return (exec_cmd(minishell));
}
