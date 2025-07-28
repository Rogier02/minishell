/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_append_exit_code.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 17:48:34 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/27 19:36:59 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_append_exit_code(t_minishell *minishell, t_expansion *expan, \
								char *line, int *i)
{
	char	*exit_code_s;
	char	*temp;

	(void)line;
	exit_code_s = ft_itoa(minishell->exit_code);
	if (!exit_code_s)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, exit_code_s);
	if (!temp)
		return (free(exit_code_s), -1);
	free(expan->expanded_input);
	free(exit_code_s);
	expan->expanded_input = temp;
	(*i) += 1;
	return (0);
}