/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_append_variable.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 17:49:49 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:28:23 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_envp *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

int	heredoc_append_variable(t_minishell *minishell, t_expansion *expan,\
							char *line, int *i)
{
	char	*temp;
	int		j;

	j = 1;
	while (line[*i + j] && (ft_isalnum(line[*i + j]) || line[*i + j] == '_'))
		j++;
	expan->var_name = ft_substr(line, *i + 1, j - 1);
	if (!expan->var_name)
		return (-1);
	expan->var_expanded = get_env_value(minishell->envp, expan->var_name);
	if (!expan->var_expanded)
		expan->var_expanded = ft_strdup("");
	temp = ft_strjoin(expan->expanded_input, expan->var_expanded);
	if (!temp)
		return (-1);
	free(expan->expanded_input);
	expan->expanded_input = temp;
	*i += j;
	return (0);
}
