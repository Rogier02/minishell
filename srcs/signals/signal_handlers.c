/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/09 17:08:44 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/05 16:24:52 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

void	handle_shell_signals(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
   	 	rl_replace_line("", 0);
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
		ft_putstr_fd("canceled heredoc\n", 2);
		rl_replace_line("", 0);
		//ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		exit(130);
	}
}

void	handle_after_heredoc_signals(int signal,\
								siginfo_t *info, void *ucontext)
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

void	handle_exec_signals(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	(void)signal;
	if (signal == SIGUSR1)
		ft_putchar_fd('\n', 1);
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_ignore_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
