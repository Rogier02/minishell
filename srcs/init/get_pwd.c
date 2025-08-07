/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 16:16:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/07 19:06:37 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_minishell *minishell)
{
	t_envp		*head;
	char		*pwd;

	head = minishell->envp;
	if (head == NULL)
		printf("is NUll");
	pwd = NULL;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			pwd = ft_strdup(head->value);
			if (pwd == NULL)
				error_and_exit("malloc failure\n", minishell);
			break ;
		}
		head = head->next;
	}
	minishell->pwd = pwd;
	return (0);
}