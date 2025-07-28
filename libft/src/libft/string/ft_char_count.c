/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char_count.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 14:23:50 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/05/18 20:04:36 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_char_count(char	*str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str || c == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
