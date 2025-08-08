/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minishell.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:34:37 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 17:23:53 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char *envp[])
{
	get_envp(minishell, envp);
	if (get_pwd(minishell) == -1)
		error_and_exit("malloc failure\n", minishell);
	minishell->child = NULL;
	minishell->input = NULL;
	minishell->exit_code = 0;
	minishell->original_stdout = -1;
	minishell->original_stdin = -1;
	minishell->execution_status = 0;
	minishell->pipe_fd[WRITE_END] = -1;
	minishell->pipe_fd[READ_END] = -1;
	minishell->child = NULL;
	minishell->cmd_head = ft_calloc(1, sizeof(t_cmd_table));
	if (minishell->cmd_head == NULL)
		error_and_exit("malloc failure\n", minishell);
	minishell->cmd_current = minishell->cmd_head;
	minishell->cmd_current->infile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->infile)
		error_and_exit("malloc failure\n", minishell);
	minishell->cmd_current->outfile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->outfile)
		error_and_exit("malloc failure\n", minishell);
}
