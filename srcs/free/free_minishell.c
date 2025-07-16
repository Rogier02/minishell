/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_minishell.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/05 18:09:18 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/16 17:56:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envp_list(t_envp *envp)
{
    t_envp *tmp;
	
    while (envp)
    {
        tmp = envp->next;
        if (envp->value)
            free(envp->value);
        free(envp);
        envp = tmp;
    }
}

void	free_minishell(t_minishell *minishell)
{
    if (!minishell)
        return ;
    if (minishell->input)
        free(minishell->input);
    if (minishell->pwd)
        free(minishell->pwd);
    if (minishell->envp)
        free_envp_list(minishell->envp);
    if (minishell->cmd_head)
        free_cmd_table(minishell->cmd_head);
	if (minishell->child)
		free_children(minishell->child);
	if (close_fds(4, minishell->original_stdin, \
						minishell->original_stdout,\
						minishell->pipe_fd[READ_END], \
						minishell->pipe_fd[WRITE_END]) == -1)
		minishell->exit_code = 1;
	
}
