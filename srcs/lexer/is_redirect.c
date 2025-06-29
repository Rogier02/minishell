/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_redirect.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 14:19:38 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 14:19:49 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

int	is_redirect(t_token_type type)
{
	if (type == HERE_DOC 
		|| type == RE_APPEND 
		|| type == RE_IN 
		|| type == RE_OUT
		|| type == PIPE)
		return (1);
	return (0);
}