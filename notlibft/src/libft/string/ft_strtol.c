/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/27 17:57:31 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/14 14:39:38 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	convert_str_to_int(const char *str, int base, int sign)
{
	long	result;
	int		digit;

	result = 0;
	digit = 0;
	while (ft_isalnum(*str))
	{
		if (ft_isdigit(*str))
			digit = *str - '0';
		else if (ft_toupper(*str))
			digit = (ft_toupper(*str) - 'A' + 10);
		if (digit >= base)
			break ;
		if (sign > 0 && result > (LONG_MAX - digit) / base)
		{
			result = LONG_MIN;
			break ;
		}
		result = result * base + sign * digit;
		str++;
	}
	return (result);
}

static char	*ft_handle_sign(char *str, int *sign)
{
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long		result;
	int			sign;
	const char	*start;

	start = str;
	result = 0;
	sign = 1;
	if (base < 2 || base > 36)
	{
		if (endptr != NULL)
		{
			*endptr = (char *)start;
			return (0);
		}
	}
	while (ft_isspace(*str))
		str++;
	str = ft_handle_sign((char *)str, &sign);
	result = convert_str_to_int((char *)str, base, sign);
	while (ft_isspace(*str))
		str++;
	if (endptr != NULL)
		*endptr = (char *)str;
	return (result);
}
