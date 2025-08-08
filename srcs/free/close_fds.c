/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_fds.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/13 13:51:46 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 15:03:03 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fds(int count, ...)
{
	va_list	args;
	int		fd;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	va_start(args, count);
	while (i < count)
	{
		fd = va_arg(args, int);
		if (fd >= 0)
		{
			if (close(fd) == -1)
			{
				perror("minishell: close\n\n");
				ret = -1;
			}
		}
		i++;
	}
	va_end(args);
	return (ret);
}
