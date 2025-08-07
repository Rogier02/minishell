/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 18:22:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/02 14:54:12 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	is_literal_dollar_char(char c)
{
    if (c == '\0' || c == ' ' || c == '\t' || c == '\n')
        return (1);
    if (c == '\'' || c == '"' || c == '$')
        return (1);
    if (c == '/' || c == '\\' || c == '@' || c == '#' || c == '%')
        return (1);
    if (c == '^' || c == '&' || c == '*' || c == '(' || c == ')')
        return (1);
    if (c == '-' || c == '+' || c == '=' || c == '[' || c == ']')
        return (1);
    if (c == '{' || c == '}' || c == '|' || c == ':' || c == ';')
        return (1);
    if (c == '<' || c == '>' || c == '.' || c == ',' || c == '!')
        return (1);
    if (c == '~' || c == '`')
        return (1);
    if (ft_isdigit(c))
        return (2);
    return (0);
}

static int	is_exit_code(char *input, int i)
{
	if (input[i + 1] == '?')
		return (1);
	return (0);
}

static int is_expandable(char *input, char quote_flag, int i)
{
	if (input[i] 
		&& input[i + 1]
		&& input[i + 1] != quote_flag 
		&& input[i + 1] != ' '
		&& input[i] == '$'
		&& quote_flag != '\'')
		return (1);
	return (0);
}

static int	is_variable(t_lexing *token, int i)
{
	if (token->value[i] && token->value[i + 1])
		return (1);
	return (0);
}

int	expand(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{	
	if (is_expandable(token->value, token->quote_flag, *i))
	{
		if (is_literal_dollar_char(token->value[*i + 1]) || token->len == 1)
		{
			if (append_char(minishell, expan, token->value[*i]) == -1)
				return (-1);
		}
		else if (is_exit_code(token->value, *i))
		{
			if (append_exit_code(minishell, expan, i) == -1)
				return (-1);
		}
		else if (is_variable(token, *i))
		{
			if (append_variable(minishell, expan, token, i) == -1)
				return (-1);
		}
	}
	else if (token->value[*i])
	{
		if (append_char(minishell, expan, token->value[*i]) == -1)
			return (-1);
	} 
	return (0);
}
