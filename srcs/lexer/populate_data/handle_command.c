/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:55:27 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 20:24:45 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int append_last_command(char **array, char *command, int i)
{
	array[i] = ft_strdup(command);
	if (!array[i])
		return (-1);
	
}

static int add_command_to_table(t_minishell *minishell, t_lexing *token)
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
			return (free_array(new_array), -1);
		j++;
	}
	new_array[i] = ft_strdup(token->expanded_value);
	new_array[i + 1] = NULL;
	ft_free_array(minishell->cmd_current->cmd);
	minishell->cmd_current->cmd = new_array;
	return (0);
}

static int create_new_command_array(t_minishell *minishell, t_lexing *token)
{
	minishell->cmd_current->cmd = ft_calloc(2, sizeof(char *));
	if (!minishell->cmd_current->cmd)
	{
		ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_current->cmd[0] = ft_strdup(token->expanded_value);
	if (minishell->cmd_current->cmd)
	{
		ft_putstr_fd("malloc failure :\n", STDERR_FILENO);
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_current->cmd[1] = NULL;
	return (0);
}

int handle_command(t_minishell *minishell, t_lexing *token)
{
	if (token->type == WORD)
	{
		if (handle_quotes(token) == -1)
			return (-1);
		if (minishell->cmd_current->cmd == NULL)
		{
			create_new_command_array(minishell, token->expanded_value);
			if (!minishell->cmd_current->cmd)
				return (-1);
			return (0);
		}
		else if(add_to_command_table(minishell, token->expanded_value) == -1)
		{
			t_putstr_fd("malloc failure :\n", STDERR_FILENO);
			minishell->exit_code = ENOMEM;
			return (-1);
		}
	}
	return (0);
}