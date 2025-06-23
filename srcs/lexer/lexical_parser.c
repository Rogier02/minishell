/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:10:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/23 17:58:40 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_lexing *token_list, char *input)
{
    int i = 0;
    while (token_list)
    {
        printf("Token %d:\n", i++);
        printf("  Type: %d\n", token_list->type);
        printf("  Start: %d\n", token_list->start);
        printf("  Len: %d\n", token_list->len);
        //printf("  End: %d\n", token_list->end);
        printf("  Quote flag: %d\n", token_list->quote_flag);
        printf("  Value: '");
        for (int j = 0; j < token_list->len; j++)
            putchar(input[token_list->start + j]);
        printf("'\n");
        token_list = token_list->next;
    }
}

int	lexical_parser(t_minishell *minishell)
{
	t_lexing	*token_list;
	
	token_list = tokenizer(minishell->input);
	print_token_list(token_list, minishell->input);
	if (token_list == NULL)
	{
		ft_putstr_fd("malloc failure:\n", STDERR_FILENO);
		return (-1);
	}
	if (syntax_check(minishell->input, token_list) == -1)
	 	return (-1);
	if (get_substrings(token_list, minishell->input) == -1)
	 	return (-1);
	if (expansion(minishell, token_list) == -1)
		return (-1);
	if (populate_command_data(minishell, token_list) == -1)
	//clean_up_(token_list);
	return (0);
}

