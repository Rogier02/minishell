/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/08 18:11:36 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

static int	run_builtin(t_minishell *minishell)
{
	char	**cmd;

	cmd = minishell->cmd_table->cmd;
	if (!ft_strncmp(cmd[0], "echo", 4))
		return (ft_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(minishell, cmd));
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd());
	if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(minishell, cmd));
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(minishell, cmd));
	if (!ft_strncmp(cmd[0], "env", 3))
		return (ft_env(minishell, cmd));
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(minishell, cmd));
	return (0);
}

int	executor(t_minishell *msh)
{
	if (!msh->cmd_table || !msh->cmd_table->cmd || !msh->cmd_table->cmd[0])
		return (-1);
	if (is_builtin(msh->cmd_table->cmd[0]))
		return (run_builtin(msh));
	return (exec_cmd(msh));
}
