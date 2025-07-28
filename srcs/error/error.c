/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 18:17:55 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/25 19:12:28 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_and_exit(char *msg, t_minishell *minishell)
{
	free_minishell(minishell);
	perror(msg);
	exit(minishell->exit_code);
}