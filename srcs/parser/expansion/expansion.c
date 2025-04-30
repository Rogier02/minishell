/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:40:39 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/30 14:14:34 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_isolated(char *original_input, char quote_flag, int i)
{
	if (quote_flag == '\"' 
		&& (original_input[i + 1] == ' '
			|| original_input[i + 1] == '\0')
			|| original_input[i + 1] == '\"')
		return(1);
	else if (original_input[i + 1] == ' ' 
			|| original_input[i + 1] == '\0')
		return (1);
	return (0);
		
}

int	is_exit_code(char *original_input, char quote_flag, int i)
{
	if (quote_flag != '\'' && original_input[i + 1] == '?')
		return (1);
	return (0);
	
}

int	expand_input(t_minishell *mshell)
{
	t_expansion	expan;
	int	i;

	i = 0;
	init_expansion(mshell, &expan);
	while(mshell->input[i])
	{
		check_for_quotes(mshell, &expan);
		if (mshell->input[i] == '$')
		{
			if (is_isolated(mshell->input, expan.quote_flag, i) == 1)
				append_char(&expan, mshell->input[i]);
			else if (is_exit_code(mshell->input, expan.quote_flag, i) == 1)
				append_exit_code(&expan, mshell, &i);
			else if (expan.quote_flag == '\'')
				append_char(&expan, mshell->input[i]);
			else
				append_variable(mshell, &expan, &i);
		}
		else 
			append_char(&expan, mshell->input[i]);
		i++;
	}
	mshell->input = expan.expanded_input;
}
