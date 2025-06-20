/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:29:27 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/03 12:29:33 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((dst[i]) && (i < size))
		i++;
	while ((i + j + 1) < size && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}

// int main() 
// {
// 	char *s = "AAAAA";
// 	char *d = "bbbbb";
// 	size_t z = -2;

// 	strlcat(d,s,z);
// 	printf("%s\n", d);
// 	return 0;
// }
