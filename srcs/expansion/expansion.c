/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:40:39 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/01 20:02:17 by rgoossen      ########   odam.nl         */
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

int	handle_expansion(t_minishell *mshell, t_expansion *expan, char *input, int *i)
{
	if (is_isolated(input, expan->quote_flag, *i))
		if (append_char(expan, input[*i]) == -1)
			return (-1);
	else if (is_exit_code(input, expan->quote_flag, *i))
		if (append_exit_code(expan, mshell, i) == -1)
			return (-1);
	else if (expan->quote_flag == '\'')
		if (append_char(expan, input[*i]) == -1)
			return (-1);
	else
	{
		if (append_variable(mshell, expan, i) == -1)
			return (-1);
	}
	return (0);
}

char *expand_input(t_minishell *mshell, char *input)
{
	t_expansion	expan;
	int	i;

	i = 0;
	init_expansion(&expan);
	while(input[i])
	{
		check_for_quotes(input[i], &expan);
		if (input[i] == '$')
		{
			if (handle_expansion(mshell, input, &expan, &i) == -1)
			{
				mshell->exit_code = ENOMEM;
				return (free_expansion(&expan), NULL);
			}
		}
		else if (append_char(&expan, input[i]) == -1)
		{
			mshell->exit_code = ENOMEM;
			return (free_expansion(&expan), NULL);
		}
		i++;
	}
	printf("expaned input = %s", input);
	return (expan.expanded_input);
}
