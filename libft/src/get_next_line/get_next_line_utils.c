/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 15:51:45 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/20 14:53:04 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_ft_strdup(char *str)
{
	size_t	i;
	size_t	j;
	char	*dup;

	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	while (str[j])
		j++;
	dup = (char *)malloc(sizeof(char) * (j + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_ft_substr(char *str, size_t start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!str)
		return (NULL);
	if (start > gnl_ft_strchr(str, '\0'))
		return (gnl_ft_strdup("\0"));
	substr = (char *)malloc(sizeof(char) * (len) + 1);
	if (!substr)
		return (NULL);
	while (str[start] && i < len)
	{
		substr[i] = str[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1)
		return (NULL);
	k = 0;
	i = gnl_ft_strchr(s1, '\0');
	j = gnl_ft_strchr(s2, '\0');
	str = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	while (k < i)
	{
		str[k] = s1[k];
		k++;
	}
	while (k < i + j)
	{
		str[k] = s2[k - i];
		k++;
	}
	str[k] = '\0';
	return (str);
}

size_t	gnl_ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (++i);
		i++;
	}
	return (0);
}

void	gnl_ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return ;
}
