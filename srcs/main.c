/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 13:11:48 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_and_validate_input(t_minishell *minishell)
{
	set_signal_protocal(minishell, main_shell);
	minishell->input = readline("minishell:~$ ");
	if (!minishell->input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (-1);
	}
	if (ft_strlen(minishell->input) == 0 && minishell->input != NULL)
		return (0);
	add_history(minishell->input);
	if (has_syntax_error(minishell->input) == 1)
	{
		free(minishell->input);
		return (0);
	}
	return (1);
}

static int	parse_and_execute(t_minishell *minishell)
{
	int	parse_status;

	parse_status = lexical_parser(minishell);
	if (parse_status == 1)
	{
		reset_data(minishell);
		free(minishell->input);
		return (0);
	}
	if (parse_status == -1)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	if (executor(minishell) == -1)
		ft_putstr_fd("minishell: execution failed\n", STDERR_FILENO);
	reset_data(minishell);
	free(minishell->input);
	return (1);
}

static void	run_minishell(t_minishell *minishell)
{
	int	input_status;

	while (1)
	{
		input_status = get_and_validate_input(minishell);
		if (input_status == -1)
			break ;
		if (input_status == 0)
			continue ;
		parse_and_execute(minishell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("Nope\n", 2);
		return (2);
	}
	init_minishell(&minishell, envp);
	set_signal_protocal(&minishell, main_shell);
	run_minishell(&minishell);
	rl_clear_history();
	free_minishell(&minishell);
	return (0);
}
