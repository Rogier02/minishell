/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_variable_2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 17:36:04 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/26 17:39:41 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_name(char *input, char quote_flag, int i)
{
	char	*variable_name;
	int		j;

	j = 0;
	i = i + 1;
	while(input[i + j]
		&& (ft_isalnum(input[i + j])
			|| input[i + j] == '_'))
	{
		if (input[i + j] == quote_flag)
			break;
		j++;
	}
	variable_name = ft_substr(input, i, j);
	if (variable_name == NULL)
		return (NULL);
	return (variable_name);
}

int	variable_located(t_expansion *expan, t_envp *head)
{
	if (ft_strncmp(head->value, expan->var_name, expan->var_name_len) == 0)
		return (0);
	return (1);
}

int expand_variable(char *envp_value, t_expansion *expan)
{
	expan->var_expanded = ft_substr(envp_value, expan->var_name_len + 1, \
		ft_strlen(envp_value) - expan->var_name_len - 1);
	if (!expan->var_expanded)
		return (-1);
	return(0);
}