/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 20:21:51 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 20:23:34 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_malloc_failure(t_minishell *minishell)
{
	ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
	minishell->exit_code = ENOMEM;
	return (-1);
}