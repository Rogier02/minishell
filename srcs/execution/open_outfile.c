/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_outfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/13 14:14:57 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/13 17:19:56 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_append(t_minishell *minishell)
{
	if (minishell->cmd_current->outfile->type_flag == RE_APPEND)
	{
		if (minishell->cmd_current->outfd != -1)
		{
			if (close(minishell->cmd_current->outfd) == -1)
				return (perror("minishell: close: failed to close outfd"), -1);
			minishell->cmd_current->outfd = -1;
		}
		minishell->cmd_current->outfd = \
			open(minishell->cmd_current->outfile->name, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (minishell->cmd_current->outfd == -1)
			return (perror("minishell: open: failed to open outfd append"), -1);
	}
	return (0);
}
static int	open_truncate(t_minishell *minishell)
{
	if (minishell->cmd_current->outfile->type_flag != RE_APPEND)
	{
		if (minishell->cmd_current->outfd != -1)
		{
			if (close(minishell->cmd_current->outfd) == -1)
				return (perror("minishell: close: failed to close outfd"), -1);
			minishell->cmd_current->outfd = -1;
		}
		minishell->cmd_current->outfd = \
			open(minishell->cmd_current->outfile->name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (minishell->cmd_current->outfd == -1)
			return (perror("minishell: open: failed to open outfd"), -1);
	}
	return (0);
}

int open_outfile(t_minishell *minishell)
{
	if (open_truncate(minishell) == -1)
		return (-1);
	if (open_append(minishell) == -1)
		return (-1);
}