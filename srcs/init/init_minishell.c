/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minishell.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:34:37 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/03 16:16:46 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_envp(t_minishell *minishell)
// {
// 	t_envp *head;
	
// 	head = minishell->envp;
// 	while (head)
// 	{
// 		printf("%s\n", head->value);
// 		head = head->next;
// 	}
// }

void	init_minishell(t_minishell *minishell, char *envp[])
{
	int i;

	i = 0;
	get_envp(minishell, envp);
	//print_envp(minishell);
	get_pwd(minishell);
	minishell->main_process_pid = getpid();
	minishell->input = NULL;
	minishell->exit_code = 0;
	minishell->cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (minishell->cmd_table == NULL)
		error_and_exit("malloc failure\n", minishell);
}