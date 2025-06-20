/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:03:52 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/21 14:04:08 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strcount(int n)
{
	size_t	counter;

	counter = 1;
	if (n < 0)
		counter++;
	while (n / 10)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	count;
	int		negative;

	negative = 0;
	count = ft_strcount(n);
	str = (char *)ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		negative = 1;
	while (count--)
	{
		str[count] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
