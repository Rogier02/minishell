/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
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
		return (builtin_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (builtin_cd(minishell, cmd));
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (builtin_pwd());
	if (!ft_strncmp(cmd[0], "export", 7))
		return (builtin_export(minishell, cmd));
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (builtin_unset(minishell, cmd));
	if (!ft_strncmp(cmd[0], "env", 3))
		return (builtin_env(minishell, cmd));
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (builtin_exit(minishell, cmd));
	return (0);
}

static void	exec_external_child(t_minishell *msh)
{
	char	*cmd;
	char	*cmd_path;

	cmd = msh->cmd_table->cmd[0];
	cmd_path = get_cmd_path(cmd, msh->envp);
	if (cmd_path)
		execve(cmd_path, msh->cmd_table->cmd, NULL);
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(127);
}

static int	run_exection_cmd(t_minishell *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_external_child(msh);
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (ft_putstr_fd("minishell: fork failed\n", 2), -1);
	return (0);
}

int	execution(t_minishell *msh)
{
	if (!msh->cmd_table || !msh->cmd_table->cmd || !msh->cmd_table->cmd[0])
		return (-1);
	if (is_builtin(msh->cmd_table->cmd[0]))
		return (run_builtin(msh));
	return (run_exection_cmd(msh));
}
