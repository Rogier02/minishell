/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/08 19:24:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 19:24:51 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_check(t_minishell *minishell, char **args)
{
	if (args[2])
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		minishell->exit_code = 1;
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

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (arg_check(minishell, args))
		return (1);
	error = ft_atoi(args[1]);
	exit((unsigned char)error);
}
