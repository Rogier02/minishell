/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_redirect.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 14:19:38 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/06 10:41:40 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

int is_redirect(t_token_type type)
{
	if (type == HERE_DOC
		|| type == RE_APPEND
		|| type == RE_IN
		|| type == RE_OUT)
	{
		return (1);
	}
	return (0);
}

int	is_redirect_or_pipe(t_token_type type)
{
	if (type == HERE_DOC 
		|| type == RE_APPEND 
		|| type == RE_IN 
		|| type == RE_OUT
		|| type == PIPE)
		return (1);
	return (0);
}