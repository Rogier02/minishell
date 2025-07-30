/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_whitespaces.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/28 13:37:59 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/30 16:11:58 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_whitespaces(char *input, int *index)
{
	while (input[*index] && input[*index] == ' ')
		(*index) += 1;
}

int	is_only_whitespaces(char *input)
{
    int	i;

    if (!input)
        return (1);
    i = 0;
    while (input[i])
    {
        if (!ft_isspace(input[i]))
            return (0);
        i++;
    }
    return (1);
}