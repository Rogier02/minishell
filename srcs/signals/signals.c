/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 17:52:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/05 15:02:39 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_signals(struct sigaction *sa, t_minishell *minishell)
{
	int	sig_call_status;

	sig_call_status = 0;
	sa->sa_sigaction = handle_shell_signals;
	signal(SIGQUIT, SIG_IGN);
	sig_call_status += sigaction(SIGINT, sa, 0);
	sig_call_status += sigaction(SIGUSR1, sa, 0);
	if(sig_call_status)
	{
		if (minishell)
			error_sig_failure("sig failure\n", minishell);
		else
		{
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
	}
	
}

void	exec_signals(struct sigaction *sa, t_minishell *minishell)
{
    int	sig_call_status;

    sig_call_status = 0;
    sa->sa_sigaction = handle_exec_signals;
    // Don't ignore SIGQUIT during execution - let it pass to children
    signal(SIGQUIT, SIG_DFL);  // Default handling for children
	sig_call_status += sigaction(SIGINT, sa, 0);
	sig_call_status += sigaction(SIGQUIT, sa, 0);
	sig_call_status += sigaction(SIGUSR1, sa, 0);
    // Remove duplicate SIGQUIT setup
    if(sig_call_status)
    {
        if (minishell)
            error_sig_failure("sig failure\n", minishell);
        else
        {
            free_minishell(minishell);
            exit(EXIT_FAILURE);
        }
    }
}

void	heredoc_signals(struct sigaction *sa, t_minishell *minishell)
{
	int	sig_call_status;

	sig_call_status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	sa->sa_sigaction = handle_heredoc_signals;
	sig_call_status += sigaction(SIGINT, sa, 0);
	if(sig_call_status)
	{
		if (minishell)
			error_sig_failure("sig failure\n", minishell);
		else
		{
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
	}

}

void	after_heredoc_signals(struct sigaction *sa,	t_minishell *minishell)
{
	int	ret;

	ret = 0;
	sa->sa_sigaction = handle_after_heredoc_signals;
	ret += sigaction(SIGINT, sa, 0);
	signal(SIGQUIT, SIG_IGN);
	if (ret)
	{
		if (minishell)
			error_sig_failure("signal handler error", minishell);
		else
		{
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
	}
}

void	set_signal_protocal(t_minishell *minishell, int location)
{
    struct sigaction	sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO; 
    sigemptyset(&sa.sa_mask);

    if (location == main_shell)
    {
        shell_signals(&sa, minishell);
    }
    else if (location == heredoc)
    {
        heredoc_signals(&sa, minishell);
    }
    else if (location == execution)
    {
        exec_signals(&sa, minishell);
    }
	else if (location == after_heredoc)
	{
		after_heredoc_signals(&sa, minishell);
	}
}