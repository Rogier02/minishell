/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nullify.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 14:22:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/05/18 20:04:40 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nullify(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}
