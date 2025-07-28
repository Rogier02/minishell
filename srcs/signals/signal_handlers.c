/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/09 17:08:44 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/19 18:13:01 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_heredoc_interrupted = 0;

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

void	handle_heredoc_signals(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;

	if (signal == SIGINT)
	{	
		g_heredoc_interrupted = 1;
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	handle_child_signals(int signal, siginfo_t *info, void *ucontext)
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


