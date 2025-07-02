/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 18:11:36 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/03 01:09:56 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_builtin(t_minishell *msh)
{
	char	**cmd;

	cmd = msh->cmd_table->cmd;
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd), 1);
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(msh, cmd), 1);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(), 1);
	if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(msh, cmd), 1);
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(msh, cmd), 1);
	if (!ft_strncmp(cmd[0], "env", 3))
		return (ft_env(msh, cmd), 1);
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(msh, cmd), 1);
	return (0);
}

static int	single_builtin(t_minishell *msh, t_cmd_table *cmd)
{
	if (cmd && !cmd->next && !cmd->infile && !cmd->outfile && run_builtin(msh))
		return (1);
	return (0);
}

int	executor(t_minishell *msh)
{
	if (single_builtin(msh, msh->cmd_table))
		return (0);
	return (exec_loop(msh));
}
