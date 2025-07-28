/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_delimiter.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:34:59 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 15:35:16 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	return (strchr(" \t\n|<>", c) != NULL);
}