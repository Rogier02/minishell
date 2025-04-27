/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/27 17:51:27 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_minishell minishell;

	(void)argv;
	if (argc > 1)
	{
		// TODO return simple error to 2.
	}
	override_signals();
	init_minishell(&minishell, envp);
	// run_minishell();
	// rl_clear_history();
	// exit_minishell();
}