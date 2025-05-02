/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_variable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:08:08 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/02 18:34:04 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable_name(t_minishell *mshell, char quote_flag, int i)
{
	char	*variable_name;
	int		j;

	j = 0;
	i = i + 1;
	while(mshell->input[i + j]
		&& (ft_isalnum(mshell->input[i + j])
			|| mshell->input[i + j] == '_'))
	{
		if (mshell->input[i + j] == quote_flag)
			break;
		j++;
	}
	variable_name = ft_substr(mshell->input, i, j);
	if (variable_name == NULL)
		return (NULL);
	return (variable_name);
}

static int	variable_located(t_minishell *mshell, char *var_name, int var_name_len)
{
	if (ft_strncmp(mshell->envp->value, var_name, var_name_len) == 0)
		return (0);
	return (1);
}

static int expand_variable(char *envp_value, t_expansion *expan)
{
	expan->var_expanded = ft_substr(envp_value, expan->var_name_len + 1, \
		ft_strlen(envp_value) - expan->var_name_len - 1);
	if (!expan->var_expanded)
		return (-1);
	return(0);
}

int	append_variable(t_minishell *mshell, t_expansion *expan, int *i)
{
	t_envp	*head;
	char	*temp;
	
	expan->var_name = get_variable_name(mshell, expan->quote_flag, *i);
	if (expan->var_name == NULL)
		return (-1);
	expan->var_name_len = ft_strlen(expan->var_name);
	head = mshell->envp;
	while (head->next)
	{
		if (variable_located(mshell, expan->var_name, expan->var_name_len) == 0)
		{
			if (expand_variable(mshell->envp->value, expan) == -1)
				return (-1);
			break ;
		}
		mshell->envp = mshell->envp->next;
	}
	if(expan->var_expanded == NULL)
		expan->var_expanded = ft_strdup("");
	if (!expan->var_expanded)
		return (-1);
	temp = ft_strjoin(expan->expanded_input, expan->var_expanded);
	if (temp == NULL)
		return (-1);
	free(expan->expanded_input);
	expan->expanded_input = temp;
	(*i) += expan->var_name_len;
	return (0);
}
