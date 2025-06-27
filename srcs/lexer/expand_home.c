/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_home.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 19:13:57 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/27 15:44:06 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home(t_minishell *minishell)
{
	t_envp	*head;
	char	*home;

	head = minishell->envp;
	while (head)
	{
		if (ft_strncmp(head->value, "HOME=", 5))
		{
			home = ft_strdup(head->value + 5);
			if (home == NULL)
			{
				minishell->exit_code = ENOMEM;
				error_and_exit("malloc failure\n", minishell);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (home);
}