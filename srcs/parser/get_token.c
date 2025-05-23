/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_token.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 15:53:33 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/21 13:06:43 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static is_meta_char(t_parsing *p, char *input)
{
	if (input[p->index] == '<' 
		|| input[p->index] == '>' 
		|| input[p->index] == '|')
		return (1);
	return (0);
}

static int skip_meta_character(t_parsing *p, char *input)
{
	if ((input[p->index] == '<' || input[p->index] == '>') 
				&& (input[p->index + 1] == input[p->index]))
	{
		p->token.len += 2;
		return (2);
	}
	else
	{
		p->token.len += 1;
		return (1);
	}
}

t_token get_token(t_parsing *p, char *input)
{
	t_token token;

	init_token(&token, p->index);
	while (input[p->index])
	{
		check_quotes(input[p->index], &token.quote_flag);
		if (input[p->index] == ' ' && token.quote_flag == 0)
			break;
		if (is_meta_char(input, p->index) == 1 
			&& token.quote_flag == 0 
			&& p->token.len == 0)
		{
			p->index += skip_meta_chars(input, &p->index, &token);
			break ;
		}
		p->token.len++;
		p->index++;
	}
	skip_whitespaces(input, &p->index);
	p->token.type = get_token_type(input, token);
	p->token.end = p->index;
	return (token);
}