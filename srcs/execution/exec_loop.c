/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/03 00:59:26 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/03 01:09:36 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_infile(t_minishell *msh, t_cmd_table *cmd)
{
	int	infd;

	infd = open(cmd->infile, O_RDONLY);
	if (infd < 0)
		error_and_exit(cmd->infile, msh);
	dup2(infd, STDIN_FILENO);
	close(infd);
}

static void	handle_outfile(t_minishell *msh, t_cmd_table *cmd)
{
	int	flags;
	int	outfd;

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

static void	run_parent(int *in_fd, int *fd, t_cmd_table *cmd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
}

static void	run_child(t_cmd_table *cmd, int in_fd, int *fd,
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

int	exec_loop(t_minishell *msh)
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
			run_child(cmd, in_fd, fd, msh);
		run_parent(&in_fd, fd, cmd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	return (0);
}
