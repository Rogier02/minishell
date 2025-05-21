/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 16:16:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/03 13:50:32 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(t_minishell *minishell)
{
	t_envp	*head;
	
	head = minishell->envp;
	while (head != NULL)
	{
		//printf("hello\n");
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			minishell->pwd = ft_strdup(head->value + 4);
			if (minishell->pwd == NULL)
				error_and_exit("malloc failure\n", minishell);
			break;
		}
		head = head->next;
	}
}