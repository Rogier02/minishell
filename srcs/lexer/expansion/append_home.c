/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_home.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 19:13:57 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/28 18:37:49 by rgoossen      ########   odam.nl         */
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

int	append_home(t_minishell *minishell, t_expansion *expan)
{
	t_envp	*head;
	char	*home;
	char	*temp;
		
	head = minishell->envp;
	home = expand_home(minishell);
	if (!home)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, home);
	if (!temp)
	{
		minishell->exit_code = ENOMEM;
		ft_putstr_fd("malloc failure \n", STDERR_FILENO);
		return (free(home), -1);
	}
	free(expan->expanded_input);
	expan->expanded_input = temp;
	return (0);
}