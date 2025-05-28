/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_whitespaces.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/28 13:37:59 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/28 13:49:55 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_whitespaces(char *input, int *index)
{
	while (input[*index] && input[*index] == ' ')
		(*index)++;
}

