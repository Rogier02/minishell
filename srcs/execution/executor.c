/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/24 01:43:37 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_builtin(t_minishell *minishell)
{
	char	**cmd;

	cmd = minishell->cmd_table->cmd;
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

int	executor(t_minishell *msh)
{
	if (!msh->cmd_table || !msh->cmd_table->cmd || !msh->cmd_table->cmd[0])
		return (-1);
	if (run_builtin(msh))
		return (0);
	return (exec_cmd(msh));
}
