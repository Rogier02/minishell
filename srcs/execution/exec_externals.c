/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_externals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/10 13:57:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/03 16:04:22 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void collect_child_pid(t_minishell *minishell, int pid)
{
	t_child_p *new_child;
	t_child_p *current;

	current = minishell->child;
	new_child = malloc(sizeof(t_child_p));
	if (!new_child)
	{
		perror("minishell: malloc: failed to allocate memory for child process");
		minishell->exit_code = 1;
		return ;
	}
	new_child->pid = pid;
	new_child->next = NULL;
	if (!minishell->child)
		minishell->child = new_child;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_child;
	}
}

void	execute_externals_and_pipes(t_minishell *minishell, int *pid)
{
	handle_ignore_signals();
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork: fork failure");
		return;
	}
	if (*pid == 0)
		run_child(minishell);
	collect_child_pid(minishell, *pid);
}