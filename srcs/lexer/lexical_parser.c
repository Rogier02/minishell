/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:10:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 14:43:09 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_lexing *token_list, char *input)
{
    int i = 0;
	t_lexing *current = token_list;
    while (current)
    {
        printf("Token %d:\n", i++);
        printf("  Type: %d\n", current->type);
        printf("  Start: %d\n", current->start);
        printf("  Len: %d\n", current->len);
        //printf("  End: %d\n", current->end);
        printf("  Quote flag: %d\n", current->quote_flag);
        printf("  Value: '");
        for (int j = 0; j < current->len; j++)
            putchar(input[current->start + j]);
        printf("'\n");
        current = current->next;
    }
}

void	print_token_values(t_lexing *token_list, int loc)
{
    int i = 0;
    t_lexing *current = token_list; // Use a temp pointer
    if (loc == 1)
        printf("\n\n-------before expansion--------\n");
    if (loc == 2)
        printf("\n\n-------after expansion---------\n");
    while (current)
    {
        printf("Token %d value: '", i++);
        if (current->len > 0 && current->value)
            printf("%s", current->value);
        else if (current->len == 0)
            printf("(empty)");
        printf("', expanded: '");
        if (current->expanded_value)
            printf("%s", current->expanded_value);
        else
            printf("(none)");
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
	print_token_values(token_list, 1);
	if (expansion(minishell, token_list) == -1)
		return (-1);
	print_token_values(token_list, 2);
	//if (populate_command_data(minishell, token_list) == -1)
	//clean_up_(token_list);
	return (0);
}

