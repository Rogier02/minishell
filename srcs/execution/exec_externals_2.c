/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_externals_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 14:05:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/07 19:37:54 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_minishell *minishell)
{
	if (open_outfile(minishell) == -1)
	{
		minishell->exit_code = 1;
		return (-1);
	}
	if (minishell->cmd_current->outfd != -1)
	{
		if (dup2(minishell->cmd_current->outfd, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

static int	redirect_input(t_minishell *minishell)
{
	if (open_infile(minishell) == -1)
	{
		minishell->exit_code = 1;
		return (-1);
	}
	if (minishell->cmd_current->infd != -1)
	{
		if (dup2(minishell->cmd_current->infd, STDIN_FILENO) == -1)
			return (-1);
	}
	return (0);
}

static void exec_child(t_minishell *minishell)
{
	char	**envp;
	char	*cmd_path;

	if (!minishell->cmd_current->cmd[0] || 
        ft_strlen(minishell->cmd_current->cmd[0]) == 0)
    {
        minishell->exit_code = 127;
        error_and_exit("minishell: command not found", minishell);
    }
    envp = env_list_to_array(minishell->envp);
    if (!envp)
    {
        minishell->exit_code = 1;
        error_and_exit("minishell: execve: failed to allocate memory for envp", minishell);
    }
    if (execve(minishell->cmd_current->cmd[0], minishell->cmd_current->cmd, envp) == -1)
    {
		// if (!envp[0])
		// 	exit(555);
        cmd_path = find_cmd_path(minishell->cmd_current->cmd[0], minishell->envp);
        if (!cmd_path)
        {
            minishell->exit_code = 127;  // Command not found
            ft_free_array(envp);
            error_and_exit("minishell: command not found", minishell);
        }
        if (execve(cmd_path, minishell->cmd_current->cmd, envp) == -1)
        {
            if (errno == EACCES)
                minishell->exit_code = 126;
            else
                minishell->exit_code = 127;
            ft_free_array(envp);
            free(cmd_path);
            error_and_exit("minishell: ", minishell);
        }
    }
}

void	run_child(t_minishell *minishell)
{
	set_signal_protocal(minishell, execution);
	if (minishell->cmd_current->infd != minishell->pipe_fd[READ_END] && 
        minishell->pipe_fd[READ_END] != -1)
	{
        if (close_and_reset_fd(&minishell->pipe_fd[READ_END]) == -1)
			error_and_exit("minishell: failed to close fd\n", minishell);
	}
    if (minishell->cmd_current->outfd != minishell->pipe_fd[WRITE_END] && 
        minishell->pipe_fd[WRITE_END] != -1)
	{
		if (close_and_reset_fd(&minishell->pipe_fd[WRITE_END]) == -1)
			error_and_exit("minishell: failed to close fd\n", minishell);
	}
	if (redirect_output(minishell) == -1)
		error_and_exit("failed to redirect the outfile", minishell);
	if (redirect_input(minishell) == -1)
		error_and_exit("failed to redirect the infile", minishell);
	
	if (check_for_builtins(minishell))
	{
		exec_builtin(minishell);
		exit_child(minishell, minishell->exit_code);  // Use the actual exit code
	}
	exec_child(minishell);
}
