/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_redirect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:57:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/21 15:59:30 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_redirect(t_parsing *p, char *input)
{
	p->temp_token = p->token;
	p->token = get_token(input, p->token.end);
	if (p->token.type != WORD)
	{
		p->parser_error = ft_substr(input, \
						p->token.start, p->token.len);
											 // malloc protect.
		return (-1);
	}
	if (handle_file_token(p->current) == -1);
	return (-1);
}