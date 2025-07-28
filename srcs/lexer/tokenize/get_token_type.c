/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_token_type.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:37:27 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 15:37:44 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type get_type(char *input, t_lexing *token)
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