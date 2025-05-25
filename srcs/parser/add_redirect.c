/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_redirect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:57:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/25 17:38:21 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_file_name()
{

}

static int handle_file_token(t_parsing *p, char *input)
{
	char	*file_name;

	file_name = get_file_name(p->token, input);
	if (!file_name)
	{
		p->parser_error = "malloc error:";
		return (-1);
	}
	if (open_file(p, file_name) == -1)
	{
		return (-1);
	}
}

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
	if (handle_file_token(p, input) == -1);
	return (-1);
}