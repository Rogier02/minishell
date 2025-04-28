/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:40:39 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/28 20:55:25 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if(is_isolated(mshell->input, expan.quote_flag, i) == 1)
				append_char(&expan, mshell->input);
			else if (is_exit_code(mshell->input, expan.quote_flag, i) == 1)
				append_exit_code(&expan, mshell, i);
			else if (is_varible(mshell->input, expan.quote_flag, i) == 1)
				append_variable(&expan, mshell, i);
			else if (in_single_q(mshell->input, expan.quote_flag, i) == 1)
				append_char(&expan.expanded_input, mshell->input[i]);
		}
		else 
			append_char(&expan.expanded_input, mshell->input);
		i++;
	}
	mshell->input = expan.expanded_input;
}
