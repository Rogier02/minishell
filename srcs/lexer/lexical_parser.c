/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:10:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 13:08:35 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_(t_lexing *head)
{
	t_lexing	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		if (head->expanded_value)
			free(head->expanded_value);
		free(head);
		head = tmp;
	}
}

int	lexical_parser(t_minishell *minishell)
{
	t_lexing	*token_list;
	int			result;

	token_list = tokenizer(minishell->input);
	if (token_list == NULL)
	{
		ft_putstr_fd("malloc failure:\n", STDERR_FILENO);
		return (-1);
	}
	if (syntax_check(minishell->input, token_list) == -1)
		return (clean_up_(token_list), 1);
	if (get_substrings(minishell->input, minishell, token_list) == -1)
		return (clean_up_(token_list), -1);
	if (expansion(minishell, token_list) == -1)
		return (clean_up_(token_list), -1);
	result = populate_command_data(minishell, token_list);
	if (result == -1)
		return (clean_up_(token_list), -1);
	if (result == 1)
		return (clean_up_(token_list), 1);
	return (clean_up_(token_list), 0);
}
