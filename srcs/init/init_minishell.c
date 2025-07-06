/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minishell.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:34:37 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/06 08:20:47 by rgoossen      ########   odam.nl         */
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
	minishell->pwd = get_pwd(minishell);
	if (!minishell->pwd)
		error_and_exit("malloc failure\n", minishell);
	minishell->child = NULL;
	minishell->input = NULL;
	minishell->exit_code = 0;
	minishell->cmd_head = ft_calloc(1, sizeof(t_cmd_table));
	if (minishell->cmd_head == NULL)
		error_and_exit("malloc failure\n", minishell);
	minishell->cmd_current = minishell->cmd_head;
	minishell->cmd_current->infile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->infile)
		error_and_exit("malloc failure\n", minishell);
	minishell->cmd_current->outfile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->outfile)
		error_and_exit("malloc failure\n", minishell);

}
