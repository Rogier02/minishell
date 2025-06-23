/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 19:54:06 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/24 00:57:06 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	digit_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

static int	arg_check(char **args)
{
	if (args[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static void	exit_with_stat(int exit_status, int status)
{
	ft_putstr_fd("exit\n", 2);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	exit(exit_status);
}

int	ft_exit(t_minishell *minishell, char **args)
{
	long long	error;
	int			exit_status;
	int			status;

	(void)minishell;
	exit_status = 0;
	status = 0;
	if (!args[1])
		exit_with_stat(exit_status, status);
	digit_check(args[1]);
	if (arg_check(args))
		return (1);
	error = ft_atoi(args[1]);
	exit((unsigned char)error);
}
