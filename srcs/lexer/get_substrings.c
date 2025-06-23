/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_substrings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 17:45:33 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/23 19:18:32 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_substrings(char *input, t_minishell *mshell, t_lexing *tokens)
{
	while (tokens)
	{
		tokens->value = ft_substr(input, tokens->start, tokens->len);
		if (tokens->value == NULL)
		{
			mshell->exit_code = ENOMEM;
			ft_putstr_fd("minishell: malloc failure\n", STDERR_FILENO);
			return (-1);
		}
		tokens = tokens->next;
	}
	return (0);
}