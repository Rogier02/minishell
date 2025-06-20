/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:33:23 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/18 07:33:28 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	ft_free(char **arr, size_t i)
{
	while (i-- > 0)
	{
		free (arr[i]);
	}
	free (arr);
}

static char	**split(char const *s, char c, char **arr, size_t i)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			arr[i] = ft_substr(s, 0, len);
			if (!(arr[i]))
			{
				ft_free(arr, i);
				return (NULL);
			}
			s = s + len;
			i++;
		}
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	len;

	len = 0;
	arr = (char **)ft_calloc((ft_count(s, c) + 1), sizeof(char *));
	if (!s || !arr)
		return (NULL);
	arr = split(s, c, arr, 0);
	return (arr);
}

// int main()
// {
// 	char const	*tab = "Hello World";
// 	char c = 32;
// 	size_t	res;
// 	char **ret; 
// 	ret = ft_split("   Hello World    ", ' ');
// 	printf("%s\n", ret[0]);
// 	printf("%s\n", ret[1]);
// 	printf("%s\n", ret[2]);
// 	printf("%s\n", ret[3]);

// 	return 0;
// }