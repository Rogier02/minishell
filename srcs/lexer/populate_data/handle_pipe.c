/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_pipe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:37:24 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 19:54:23 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_pipe(t_minishell *minishell, t_lexing *token)
{
	if (token->type == PIPE)
	{
		minishell->cmd_current->next = ft_calloc(1, sizeof(t_cmd_table));
		if (!minishell->cmd_current->next)
			return (-1);
		minishell->cmd_current = minishell->cmd_current->next;
		minishell->cmd_current->infile = ft_calloc(1, sizeof(t_file_type));
		if (!minishell->cmd_current->infile)
		{
			ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
			minishell->exit_code = ENOMEM;
			return (-1);
		}
		minishell->cmd_current->outfile = ft_calloc(1, sizeof(t_file_type));
		if (!minishell->cmd_current->outfile)
		{
			ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
			minishell->exit_code = ENOMEM;
			return (-1);
		}
		token = token->next;
	}
	return (0);
}
