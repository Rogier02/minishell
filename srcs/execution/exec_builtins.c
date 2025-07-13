/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/10 12:11:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/13 17:33:05 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_for_builtins(t_minishell *minishell)
{
		char	**cmd;

	cmd = minishell->cmd_current->cmd;
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (1);
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (1);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(), 1);
	if (!ft_strncmp(cmd[0], "export", 7))
		return (1);
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (1);
	if (!ft_strncmp(cmd[0], "env", 3))
		return (1);
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (1);
	return (0);
}

int	run_builtin(t_minishell *minishell)
{
	char	**cmd;

	cmd = minishell->cmd_current->cmd;
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