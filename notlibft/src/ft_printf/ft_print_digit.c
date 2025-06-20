/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:24:17 by rgoossen          #+#    #+#             */
/*   Updated: 2023/11/20 18:24:20 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// prints in lowercase.
int	ft_print_digit(long n, int base, char *hex)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n < 0)
	{
		write(1, "-", 1);
		return (count + ft_print_digit(-n, base, hex) + 1);
	}
	else if (n < base)
		return (count + ft_print_char(hex[n]));
	else
	{
		count += ft_print_digit(n / base, base, hex);
		return (count + ft_print_digit(n % base, base, hex));
	}
	return (count);
}

// prints pointer
int	ft_print_base(unsigned long n, int base, char *hex)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(1, "(nil)", 5));
	count += write (1, "0x", 2);
	if (n < 0)
	{
		count += write(1, "-", 1);
		return (count + ft_print_digit(-n, base, hex) + 1);
	}
	else if (n < (unsigned long)base)
		return (count + ft_print_char(hex[n]));
	else
	{
		count += ft_print_digit(n / base, base, hex);
		return (count + ft_print_digit(n % base, base, hex));
	}
	return (count);
}
