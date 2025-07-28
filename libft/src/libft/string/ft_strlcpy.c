/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:56:30 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/03 11:56:37 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
    It calculates the length of the source string (src) and stores it in src_len.

    It checks if the size is 0 and returns the required size 
	(the length of the source string) in this case.

    It copies characters from the source to the destination 
	while ensuring that there's enough room in the destination buffer and 
	leaving room for a null-terminator.

    It null-terminates the destination string explicitly.

    Finally, it returns the length of the source string (src_len).
*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (size == 0)
	{
		src_len = ft_strlen(src);
		return (src_len);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	i = ft_strlen(src);
	return (i);
}
