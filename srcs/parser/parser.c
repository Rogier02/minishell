/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/02 18:55:41 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse first then expand where needed.
int	parser(t_minishell *minishell)
{
	char *test_input = "$INV";
	char *expanded_input;

	expanded_input = expand_input(minishell, test_input);
	printf("%s", expanded_input);
	
	// if (!initial_check(minishell))
	// 	return (-1);
	// if (!parse_input(minishell))
	// 	return (-1);

	return(0);
}