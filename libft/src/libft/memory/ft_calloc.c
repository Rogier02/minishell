/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 16:13:02 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/14 14:40:05 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size > __SIZE_MAX__)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
