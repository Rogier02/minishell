/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 12:16:19 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:17:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_data(t_minishell *minishell)
{
	free_cmd_table(minishell->cmd_head);
	minishell->cmd_head = NULL;
	minishell->cmd_current = NULL;
	minishell->cmd_head = ft_calloc(1, sizeof(t_cmd_table));
	if (!minishell->cmd_head)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current = minishell->cmd_head;
	minishell->cmd_current->infile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->infile)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current->outfile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->outfile)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current->infd = -1;
	minishell->cmd_current->outfd = -1;
	ft_memset(minishell->pipe_fd, -1, sizeof(int [2]));
}
