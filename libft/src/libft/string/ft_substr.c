/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:43:33 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/14 11:43:36 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allocates (with malloc(3)) and returns a substring
// from the string ’s’.
// The substring begins at index ’start’ and is of
// maximum size ’len’.

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	j;

	if (!(s))
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!(sub))
		return (NULL);
	j = 0;
	while (j < len)
	{
		sub[j] = s[j + start];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
// int main(void)
// {
// 	printf("%s\n", ft_substr("abcdefghijklmnop", 5, 4));
// 	return 0;
// }
