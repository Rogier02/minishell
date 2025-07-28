/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:46:15 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/05 09:46:21 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *) s;
	ch = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (p[i] == ch)
			return (p + i);
		i++;
	}
	return (NULL);
}
