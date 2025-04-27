/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 16:16:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/27 16:41:31 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(t_minishell *minishell)
{
	while (minishell->envp != NULL)
	{
		printf("hello\n");
		if (ft_strncmp(minishell->envp->value, "PWD=", 4) == 0)
		{
			minishell->pwd = ft_strdup(minishell->envp->value + 4);
			if (minishell->pwd == NULL)
				error_and_exit("malloc failure\n", minishell);
			break;
		}
		minishell->envp = minishell->envp->next;
	}
}