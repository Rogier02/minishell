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

// handle infile
static void	handle_infile(t_minishell *msh, t_cmd_table *cmd)
{
	int infd;

	infd = open(cmd->infile, O_RDONLY);
	if (infd < 0)
		error_and_exit(cmd->infile, msh);
	dup2(infd, STDIN_FILENO);
	close(infd);
}

// handle outfile
static void	handle_outfile(t_minishell *msh, t_cmd_table *cmd)
{
	int flags;
	int outfd;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append_flag)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfd = open(cmd->outfile, flags, 0644);
	if (outfd < 0)
		error_and_exit(cmd->outfile, msh);
	dup2(outfd, STDOUT_FILENO);
	close(outfd);
}

static void	child_processs(t_cmd_table *cmd, int in_fd, int *fd,
		t_minishell *msh)
{
	if (cmd->infile)
		handle_infile(msh, cmd);
	else if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->outfile)
		handle_outfile(msh, cmd);
	else if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[0])
		close(fd[0]);
	msh->cmd_table = cmd;
	exec_cmd(msh);
	exit(EXIT_FAILURE);
}

static void	parent_process(int *in_fd, int *fd, t_cmd_table *cmd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
}

static int	single_builtin(t_cmd_table *cmd, t_minishell *msh)
{
	if (cmd && !cmd->next && !cmd->infile && !cmd->outfile && run_builtin(msh))
		return (1);
	return (0);
}

static int	exec_loop(t_minishell *msh)
{
	t_cmd_table	*cmd;
	int			fd[2];
	int			in_fd;
	pid_t		pid;
	int			status;

	cmd = msh->cmd_table;
	in_fd = 0;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("pipe"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
			child_processs(cmd, in_fd, fd, msh);
		parent_process(&in_fd, fd, cmd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	return (0);
}

int	executor(t_minishell *msh)
{
	if (single_builtin(msh->cmd_table, msh))
		return (0);
	return (exec_loop(msh));
}