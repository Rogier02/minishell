/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_exit_code.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:18:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/01 18:50:01 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_exit_code(t_minishell *minishell, t_expansion *expan, int *i)
{
	char	*exit_code_copy;
	char	*temp;

	exit_code_copy = ft_itoa(minishell->exit_code);
	if (exit_code_copy == NULL)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, exit_code_copy);
	if (temp == NULL)
	{
		free(exit_code_copy);
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure: \n", STDERR_FILENO);
		return (-1);
	}
	free(expan->expanded_input);
	expan->expanded_input = temp;
	(*i) += 1;
	free(exit_code_copy);
	return (0);
}
