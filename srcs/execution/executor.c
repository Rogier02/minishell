/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/12 19:49:12 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_execution_process(t_minishell *minishell, int *pid, int *statuscode)
{
	int	result;
	
	if (!minishell->cmd_head->next && check_for_builtins(minishell))
	{
		exec_single_builtin(minishell);
		restore_fds(minishell);
		set_signal_protocal(minishell, execution);
		return ;
	}
	if (minishell->cmd_current->next)
	{
		if (pipe(minishell->pipe_fd) == -1)
			return ; // TODO: correct error handling.
		handle_pipe_fds(minishell);
		execute_externals_and_pipes(minishell, pid);
	}
	set_signal_protocal(minishell, execution);
		// if no builtins were executed or there is a pipe. we run
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
	}
	wait_for_child_proccesses();
	return (exec_cmd(minishell));
}
