/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/28 14:55:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*run_minishell(t_minishell *minishell)
{
	while (1)
	{
		minishell->input = readline("minishell:~$ ");
		// initial input check. white spaces, empty line. etc
		// add input to history
		// expand input.
		// parse input
		// execute inpute
		
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell minishell;

	(void)argv;
	if (argc > 1)
	{
		// TODO return simple error to 2.
	}
	handle_signals();
	init_minishell(&minishell, envp);
	run_minishell();
	// rl_clear_history();
	// exit_minishell();
}