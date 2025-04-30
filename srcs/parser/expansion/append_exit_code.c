/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_exit_code.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:18:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/30 14:33:03 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_exit_code(t_expansion *expan, t_minishell *minishell)
{
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa(minishell->exit_code);
	temp = ft_strjoin(expan->expanded_input, exit_code);
	free(expan->expanded_input);
	expan->expanded_input = temp;	
}