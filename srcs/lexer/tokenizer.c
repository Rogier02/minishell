/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:32:35 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/23 17:29:13 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char c)
{
	return (strchr(" \t\n|<>", c) != NULL);
}

static	t_token_type get_type(char *input, t_lexing *token)
{
	if (ft_strncmp(&input[token->start], "<", token->len) == 0)
		return (RE_IN);
	else if (ft_strncmp(&input[token->start], ">", token->len) == 0)
		return (RE_OUT);
	else if (ft_strncmp(&input[token->start], ">>", token->len) == 0)
		return (RE_APPEND);
	else if (ft_strncmp(&input[token->start], "<<", token->len) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(&input[token->start], "|", token->len) == 0)
		return (PIPE);
	else 
		return (WORD);
}

static void	get_redirect_token(char *input, t_lexing *token, int *i)
{
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		*i += 2;
		token->len = 2;
		return ;
	}
	else 
	{
		*i += 1;
		token->len = 1;
	}
}

static t_lexing	*get_next_token(char *input, int *i)
{
	t_lexing	*new_token;

	new_token = ft_calloc(1, sizeof(t_lexing));
	if (!new_token)
		return (NULL); 
	new_token->start = *i;
	new_token->len = 0;
	new_token->quote_flag = '\0';
	while (input[*i])
	{
		check_quotes(input[*i], &new_token->quote_flag);
		if (is_delimiter(input[*i]) && new_token->len == 0 
			&& new_token->quote_flag == '\0')
			{
				get_redirect_token(input, new_token, i);
				break;
			}
		if (is_delimiter(input[*i]) && new_token->quote_flag == '\0')
			break ;
		*i += 1;
		new_token->len++;
	}
	skip_whitespaces(input, i);
	new_token->type = get_type(input, new_token);
	return (new_token);
}

t_lexing	*tokenizer(char *input)
{
	int			i;
	t_lexing	*current;
	t_lexing	*head;
	
	i = 0;
	skip_whitespaces(input, &i);
	current = get_next_token(input, &i);
	if (!current)
		return (NULL);
	head = current;
	current->previous = NULL;
	while (input[i])
	{	
		current->next = get_next_token(input, &i);
		if (!current->next)
		{
			return (NULL);
		}
		current->next->previous = current; 
		current = current->next;
	}
	return (head);
}
