/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_token.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:36:11 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 15:45:25 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static int		init_new_token(t_lexing *new_token, int i)
{
	new_token = ft_calloc(1, sizeof(t_lexing));
	if (!new_token)
		return (NULL); 
	new_token->start = i;
	new_token->len = 0;
	new_token->quote_flag = '\0';
}

t_lexing	*get_next_token(char *input, int *i)
{
	t_lexing	*new_token;

	if (!init_new_token(new_token, *i))
		return (NULL); 
	while (input[*i])
	{
		check_quotes(input[*i], &new_token->quote_flag);
		if (new_token->quote_flag)
			new_token->contains_quotes = true;
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
