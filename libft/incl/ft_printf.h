/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 16:32:32 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/05/18 19:16:15 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <bsd/string.h>
# include <limits.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_print_format(char format, va_list ap);
int		ft_print_char(int c);
int		ft_print_str(char *str);
int		ft_print_digit(long n, int base, char *hex);
int		ft_print_base(unsigned long n, int base, char *hex);

#endif
