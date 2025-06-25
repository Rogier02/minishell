/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:10:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/25 16:27:56 by rgoossen      ########   odam.nl         */
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

void	print_token_values(t_lexing *token_list)
{
    int i = 0;
    t_lexing *current = token_list; // Use a temp pointer
    while (current)
    {
        printf("Token %d value: '", i++);
        if (current->len > 0 && current->value)
            printf("%s", current->value);
        else if (current->len == 0)
            printf("(empty)");
        printf("'\n");
        current = current->next;
    }
}

static int		has_unclosed_quotes(char *input)
{
	int		i;
	char	quote_flag;

	i = 0;
	quote_flag = '\0';
	while (input[i])
	{	
		if (quote_flag == '\0' && (input[i] == '\\' || input[i] == ';'))
			return (1);
		if (quote_flag == '\0' 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = input[i];
		else if (quote_flag == input[i] 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = '\0';
		i++;
	}
	if (quote_flag != '\0')
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	lexical_parser(t_minishell *minishell)
{
	t_lexing	*token_list;
	
	if (has_unclosed_quotes(minishell->input) == -1)
		return (-1);
	token_list = tokenizer(minishell->input);
	print_token_list(token_list, minishell->input);
	if (token_list == NULL)
	{
		ft_putstr_fd("malloc failure:\n", STDERR_FILENO);
		return (-1);
	}
	if (syntax_check(minishell->input, token_list) == -1)
	 	return (-1);
	if (get_substrings(minishell->input, minishell, token_list) == -1)
	 	return (-1);
	print_token_values(token_list);
	if (expansion(minishell, token_list) == -1)
		return (-1);
	print_token_values(token_list);
	if (populate_command_data(minishell, token_list) == -1)
	//clean_up_(token_list);
	return (0);
}

