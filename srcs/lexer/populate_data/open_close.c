/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_close.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/30 17:18:56 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/07 12:27:07 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_and_close_file(t_minishell *minishell)
{
	int	fd;

	if (minishell->cmd_current->outfile->type_flag == RE_OUT)
		fd = open(minishell->cmd_current->outfile->name, \
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (minishell->cmd_current->outfile->type_flag == RE_APPEND)
		fd = open(minishell->cmd_current->outfile->name, \
										O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0); // Don't need to open input files early
	if (fd == -1)
	{
		perror(minishell->cmd_current->outfile->name);
		minishell->exit_code = 1;
		return (-1);
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}

