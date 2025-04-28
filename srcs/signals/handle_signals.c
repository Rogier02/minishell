/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_signals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 17:52:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/28 18:01:43 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(t_minishell *minishell, int loc)
{
		struct sigaction	sa;

		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_flags = SA_SIGINFO; // tells the Union to use sigaction funciton pointer
		sigemptyset(&sa.sa_mask); // dont block signals.

		if (loc == 1)
		{
			execution_signal_handler(&sa);

		}
		if (loc == 2)
		{
			heredoc_signal_handler(&sa);
		}
		if (loc == 3)
		{
			child_process_signal_handler(&sa);
		}
		// add signal handler function for execution
		// add singal handler function for heredoc
		// add signal handler function for child process
		
}