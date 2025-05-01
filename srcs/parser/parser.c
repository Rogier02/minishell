/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/01 18:06:49 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse first then expand where needed.
int	parser(t_minishell *minishell)
{
	if (!initial_check(minishell))
		return (-1);
	if (!parse_input(minishell))
		return (-1);

	
}