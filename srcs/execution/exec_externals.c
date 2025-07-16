/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_externals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/10 13:57:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/16 18:02:20 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_externals_and_pipes(t_minishell *minishell, int *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("minishell: fork: fork failure\n"), -1);
	if (*pid == 0)
		run_child(minishell);
}