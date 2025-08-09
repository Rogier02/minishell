/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   field_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 14:20:42 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:51:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
	while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

char	**split_on_whitespace(char *str)
{
	int		i;
	int		j;
	int		count;
	int		start;
	char	**result;

	count = count_words(str);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		start = i;
		while (str[i] && !ft_isspace(str[i]))
			i++;
		if (i > start)
			result[j++] = ft_substr(str, start, i - start);
	}
	result[j] = NULL;
	return (result);
}

static int	add_split_command_to_table(t_minishell *minishell,\
	char *command_str)
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
	new_array[i] = ft_strdup(command_str);
	if (!new_array[i])
		return (ft_free_array(new_array), -1);
	new_array[i + 1] = NULL;
	ft_free_array(minishell->cmd_current->cmd);
	minishell->cmd_current->cmd = new_array;
	return (0);
}

int	field_split_add(t_minishell *minishell, t_lexing *token)
{
	char	**split;
	int		k;

	if (minishell->cmd_current->cmd == NULL)
	{
		minishell->cmd_current->cmd = ft_calloc(1, sizeof(char *));
		if (!minishell->cmd_current->cmd)
			return (-1);
	}
	split = split_on_whitespace(token->expanded_value);
	if (!split)
		return (-1);
	k = 0;
	while (split && split[k])
	{
		if (add_split_command_to_table(minishell, split[k]) == -1)
		{
			ft_free_array(split);
			return (-1);
		}
		k++;
	}
	ft_free_array(split);
	return (0);
}
