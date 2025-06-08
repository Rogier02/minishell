/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 23:00:15 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/08 23:00:15 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
4096 is maximum path length on linux,
so we kind of avoiding any scenerio that would end with overflowing the buffer 
*/

#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	ft_putstr_fd("pwd: error.\n", STDERR_FILENO);
	return (1);
}
