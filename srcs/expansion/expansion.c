/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:40:39 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/21 16:23:22 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_isolated(char *original_input, char quote_flag, int i)
{
	if (quote_flag == '\"' 
		&& (original_input[i + 1] == ' '
			|| original_input[i + 1] == '\0'
			|| original_input[i + 1] == '\"'))
		return(true);
	else if (original_input[i + 1] == ' ' 
			|| original_input[i + 1] == '\0')
		return (true);
	return (false);
}

static bool	is_exit_code(char *original_input, char quote_flag, int i)
{
	if (quote_flag != '\'' && original_input[i + 1] == '?')
		return (true);
	return (false);
}

int	handle_expansion(t_expansion *expan, char *input, int *i)
{
	if (input[*i] == '$')
	{
		if (is_isolated(input, expan->quote_flag, *i))
		{
			if (append_char(expan, input[*i]) == -1)
				return (-1);
		}
		else if (is_exit_code(input, expan->quote_flag, *i))
		{
			if (append_exit_code(expan, i) == -1)
				return (-1);
		}
		else if (expan->quote_flag == '\'')
		{
			if (append_char(expan, input[*i]) == -1)
				return (-1);
		}
		else if (append_variable(expan, input, i) == -1)
		{
			return (-1);
		}
	}
	return (0);
}

static void init_expansion(t_minishell *mshell, t_expansion *expan, int *i)
{
	expan->expanded_input = NULL;
	expan->var_expanded = NULL;
	expan->var_name = NULL;
	expan->quote_flag = 0;
	expan->var_name_len = 0;
	expan->envp_copy = mshell->envp;
	expan->exit_code_copy = mshell->exit_code;
	*i = 0;
}

int expand_input(t_minishell *mshell)
{
	t_expansion	expan;
	int	i;

	init_expansion(mshell, &expan, &i);
	while(mshell->input[i])
	{
		check_quotes(mshell->input[i], &expan.quote_flag);
		if (append_heredoc(mshell->input, &expan, &i) == -1)
		{
				mshell->exit_code = ENOMEM;
				return (free_expansion(&expan), -1);
		}
		else if (handle_expansion(&expan, mshell->input, &i) == -1)
		{
			mshell->exit_code = ENOMEM;
			return (free_expansion(&expan), -1);
		}
		else if (append_char(&expan, mshell->input[i]) == -1)
		{
			mshell->exit_code = ENOMEM;
			return (free_expansion(&expan), -1);
		}
		i++;
	}
	free(mshell->input);
	mshell->input = expan.expanded_input;
	return (0);
}
