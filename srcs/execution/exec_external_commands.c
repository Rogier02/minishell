/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external_commands.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/10 13:57:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/11 18:41:02 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external_command(t_minishell *minishell)
{
	minishell->child->pid = fork();
	if ()
}