/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_and_kill.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 12:36:53 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 12:38:10 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_and_kill(t_minishell *minishell)
{
	kill_all_children(minishell);
	wachter(minishell);
	minishell->exit_code = 1;
	return (-1);
}
