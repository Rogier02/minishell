/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_and_reset_fd.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/25 15:19:01 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 15:02:08 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_and_reset_fd(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (-1);
		*fd = -1;
	}
	return (0);
}
