/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_redirect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:57:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/28 17:14:03 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_file_name(t_token token, char *input)
{
	char	*file_name;
	int		len;

	len = token.end - token.start;
	file_name = ft_substr(input, token.start, len);
	if (!file_name)
		(NULL);
	return (file_name);
}

static int handle_file_type(t_parsing *p, char *input)
{
	char	*file_name;

	file_name = get_file_name(*p->token, input);
	if (!file_name)
	{
		p->parser_error = "malloc error:";
		return (-1);
	}
	if (p->previous_token->type == HERE_DOC)
		handle_heredoc(p, file_name);
	if (open_file(p, file_name) == -1)
		return (-1);
	return (0);
}

int add_redirect(t_parsing *p, char *input)
{
	p->previous_token = p->token;
	get_token(p, input);
	if (p->token->type != WORD)
	{
		p->parser_error = ft_substr(input, \
						p->token->start, p->token->len);
								 // malloc protect.
		return (-1);
	}
	if (handle_file_type(p, input) == -1)
		return(-1);
	return (0);
}