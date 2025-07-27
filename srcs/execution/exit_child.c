/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_child.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 15:12:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/27 15:14:00 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_child(t_minishell *minishell, int exit_code)
{
	free_minishell(minishell);
	exit(exit_code);
}