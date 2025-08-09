/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:55:27 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:54:25 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_command_to_table(t_minishell *minishell, t_lexing *token)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (minishell->cmd_current->cmd[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return (-1);
	while (j < i)
	{
		new_array[j] = ft_strdup(minishell->cmd_current->cmd[j]);
		if (!new_array[j])
			return (ft_free_array(new_array), -1);
		j++;
	}
	new_array[i] = ft_strdup(token->expanded_value);
	new_array[i + 1] = NULL;
	ft_free_array(minishell->cmd_current->cmd);
	minishell->cmd_current->cmd = new_array;
	return (0);
}

static int	creat_array(t_minishell *minishell, t_lexing *token)
{
	(void) token;
	init_fds(minishell->cmd_current);
	minishell->cmd_current->cmd = ft_calloc(1, sizeof(char *));
	if (!minishell->cmd_current->cmd)
	{
		ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_current->cmd[0] = NULL;
	return (0);
}

int	handle_command(t_minishell *minishell, t_lexing *t)
{
	if (t->type == WORD)
	{
		if (!t->expanded_value || ft_strlen(t->expanded_value) == 0)
			return (0);
		if ((t->previous && !is_redirect(t->previous->type)) || !t->previous)
		{
			if (handle_quotes(t) == -1)
				return (-1);
			if (minishell->cmd_current->cmd == NULL)
			{
				if (creat_array(minishell, t) == -1
					|| !minishell->cmd_current->cmd)
					return (-1);
			}
			if (!t->contains_quotes
				&& ft_strchr(t->expanded_value, ' '))
			{
				if (field_split_add(minishell, t) == -1)
					return (error_malloc_failure(minishell));
			}
			else if (add_command_to_table(minishell, t) == -1)
				return (error_malloc_failure(minishell));
		}
	}
	return (0);
}
