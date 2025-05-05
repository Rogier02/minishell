/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_token.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 15:53:33 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/05 17:48:25 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token get_token(t_parsing *p, char *input)
{
	t_token token;

	init_token(&token, p->index);
	while (input[p->index])
	{
		check_quotes(input[p->index], &token.quote_flag);
		if (input[p->index] == ' ' && token.quote_flag == 0)
			break;
		if (meta_char(input, p->index) 
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
	get_token_type(input, token);
	p->token.end = p->index;
	return (token);
}