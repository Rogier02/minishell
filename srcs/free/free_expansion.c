/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_expansion.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 17:05:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/27 19:41:12 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_expansion(t_expansion *expan)
{
    if (!expan)
        return;
    if (expan->expanded_input)
        free(expan->expanded_input);
    if (expan->var_expanded)
        free(expan->var_expanded);
    if (expan->var_name)
        free(expan->var_name);
    free(expan);
}