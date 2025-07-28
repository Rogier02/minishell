/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 16:16:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/06 08:19:13 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_minishell *minishell)
{
	t_envp	*head;
	char 	*pwd;
	
	head = minishell->envp;
	while (head != NULL)
	{
		//printf("hello\n");
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			pwd = ft_strdup(head->value);
			if (pwd == NULL)
			{
				error_and_exit("malloc failure\n", minishell);
				break;
			}
			return (pwd);
		}
		head = head->next;
	}
	return(NULL);

}