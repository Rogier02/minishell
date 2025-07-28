/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:14:31 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/17 08:14:34 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*nstr;

	nstr = 0;
	if (s1 == 0)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && s1[end - 1] && ft_strchr(set, s1[end - 1]))
		end--;
	nstr = (char *)ft_calloc((end - start + 1), sizeof(char));
	if (nstr)
		ft_memcpy(nstr, &s1[start], end - start);
	return (nstr);
}

// int main(void)
// {
// 	char res[1] = "";

// 	printf("hi%s\n", ft_strtrim(res, "x"));
// 	return 0;
// }
