/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 17:52:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 18:31:29 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_signals(struct sigaction *sa, t_minishell *minishell)
{
	//int	ret;

	(void)minishell;
	sa->sa_sigaction = handle_shell_signals;
	//signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, sa, 0);
	
}

void	heredoc_signals(struct sigaction *sa, t_minishell *minishell)
{
	//int ret;

	(void)minishell;
	sa->sa_sigaction = handle_heredoc_signals;
	sa->sa_flags = 0;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, sa, 0);

}

void	child_signals(struct sigaction *sa, t_minishell *minishell)
{
	(void)minishell;
	sa->sa_sigaction = handle_child_signals;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);	
}

void	set_signal_protocal(t_minishell *minishell, int location)
{
		struct sigaction	sa;

		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_flags = SA_SIGINFO; // tells the Union to use sigaction funciton pointer
		sigemptyset(&sa.sa_mask); // dont block signals.

		if (location == main_shell)
			shell_signals(&sa, minishell);
		if (location == heredoc)
			heredoc_signals(&sa, minishell);
		if (location == child_process)
			child_signals(&sa, minishell);
		//if (location == waiting_parent)
		//	waiting_parent_signals(&sa, minishell);
}