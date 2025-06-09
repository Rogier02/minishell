/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/09 17:08:44 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/09 19:01:14 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_shell_signals(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();	
	}
}

void	handle_heredoc_singals(int signal, sigino_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;

	if (signal == SIGINT)
	{
		//close heredoc <- this means that heredoc needs to be opend to a file descriptor
			// dont close inside the handler!! best practice to handle close and cleanup in the heredoc function.
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}


