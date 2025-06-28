/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_substrings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 17:45:33 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/28 13:56:45 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_substrings(char *input, t_minishell *mshell, t_lexing *tokens)
{
	t_lexing *current;

	current = tokens;
	while (current)
	{
		current->value = ft_substr(input, current->start, current->len);
		if (current->value == NULL)
		{
			mshell->exit_code = ENOMEM;
			ft_putstr_fd("minishell: malloc failure\n", STDERR_FILENO);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}