/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/13 16:41:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/21 19:41:25 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_minishell *minishell)
{
	if (minishell->cmd_current->infile &&
		minishell->cmd_current->infile->name)
	{
		if (minishell->cmd_current->infd != -1)
		{
			if (close(minishell->cmd_current->infd) == -1)
				return (perror("minishell: close: failed to close infd"), -1);
			minishell->cmd_current->infd = -1;
		}
		minishell->cmd_current->infd = \
			open(minishell->cmd_current->infile->name, O_RDONLY);
		if (minishell->cmd_current->infd == -1)
			return (perror("minishell: open: failed to open infd"), -1);
	}
	return (0);
}	