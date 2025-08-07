/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 18:17:55 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/02 15:39:20 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_and_exit(char *msg, t_minishell *minishell)
{
	free_minishell(minishell);
	perror(msg);
	exit(minishell->exit_code);
}

int	return_error(char *msg, t_minishell *minishell)
{
	ft_putstr_fd(msg, 2);
	minishell->exit_code = 1;
	return (1);
}

void error_sig_failure(char *msg, t_minishell *minishell)
{
	free_minishell(minishell);
	perror(msg);
	exit(EXIT_FAILURE);
}