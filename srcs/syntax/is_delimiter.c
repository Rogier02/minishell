/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_delimiter.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 18:40:55 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/22 18:41:08 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	return (strchr(" \t\n|<>", c) != NULL);
}
