/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_child.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 14:05:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/13 16:39:33 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output()
{

}

static void	redirect_input(t_minishell *minishell)
{

}

int	handle_redirects(t_minishell *minishell)
{
	if (minishell->cmd_current->outfile)
		redirect_output();
	if (minishell->cmd_current->infile)
		redirect_input();
}
void	run_child(t_minishell *minishell)
{
	if (redirect_output() == -1)
		error_and_exit("failed to redirect the outfile", minishell);
	if (redirect_input() == -1)
		eror_and_exit("failed to redirect the infile", minishell);
	exec_builtin();
	
	
	// if there is an outfile or infile. Handle_redirects
	// else if no redirects and there is a pipe handle pipe redirects. 
	
}