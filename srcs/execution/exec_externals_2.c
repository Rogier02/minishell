/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_child.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 14:05:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/16 19:15:20 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_minishell *minishell)
{
	if (open_outfile(minishell) == -1)
		return (-1);
	if (dup2(minishell->cmd_current->outfd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

static int	redirect_input(t_minishell *minishell)
{
	if (open_infile(minishell) == -1)
		return (-1);
	if (dup2(minishell->cmd_current->infd, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

static void exec_child(t_minishell *minishell)
{
	char	**envp;
	char	*cmd_path;

	envp = env_list_to_array(minishell->envp);
	if (!envp)
	{
		minishell->exit_code = 1;
		error_and_exit("minishell: execve: failed to allocate memory for envp", minishell);
	}
	cmd_path = find_cmd_path(minishell->cmd_current->cmd[0], minishell->envp);
	if (!cmd_path)
	{
		minishell->exit_code = 127;
		ft_free_array(envp);
		error_and_exit("minishell: execve: command not found", minishell);
	}
	if (execve(cmd_path, minishell->cmd_current->cmd, envp) == -1)
	{
		ft_free_array(envp);
		free(cmd_path);
		minishell->exit_code = 127;
		error_and_exit("minishell: execve: failed to execute command", minishell);
	}
}

void	run_child(t_minishell *minishell)
{
	if (redirect_output(minishell) == -1)
		error_and_exit("failed to redirect the outfile", minishell);
	if (redirect_input(minishell) == -1)
		error_and_exit("failed to redirect the infile", minishell);
	exec_child(minishell);
}
