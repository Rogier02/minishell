/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:35:29 by rgoossen          #+#    #+#             */
/*   Updated: 2023/11/17 15:35:33 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(char format, va_list ap)
{
	if (format == '%')
		return (write(1, "%", 1));
	else if (format == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (format == 's')
		return (ft_print_str(va_arg(ap, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_print_digit(va_arg(ap, int), 10, "0123456789"));
	else if (format == 'x')
		return (ft_print_digit(va_arg(ap, unsigned int), 16, \
			"0123456789abcdef"));
	else if (format == 'X')
		return (ft_print_digit(va_arg(ap, unsigned int), 16, \
			"0123456789ABCDEF"));
	else if (format == 'p')
		return (ft_print_base((unsigned long)va_arg(ap, void *), 16, \
			"0123456789abcdef"));
	else if (format == 'u')
		return (ft_print_digit(va_arg(ap, unsigned int), 10, \
			"0123456789abcdef"));
	else
		return (write(1, &format, 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count = count + ft_print_format(*(++format), ap);
		else
			count = count + write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}

// int main(void)
// {
// 	void *ptr;
// 	int len;
// 	len = ft_printf("%x\n", -1);
// 	printf("len: %d\n", len);
// 	// ft_printf("%p\n", 15);
// 	// ft_printf("%p %p\n",  ULONG_MAX, -ULONG_MAX);

// 	printf("printf:\n");
// 	len = printf("%x\n", -1);
// 	printf("len: %d\n", len);
// 	// printf("%p\n", 15);
// 	// printf("%p %p\n",  ULONG_MAX, -ULONG_MAX);
// 	return 0;
// }
