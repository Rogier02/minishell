/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_child.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 14:05:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/16 19:15:20 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_minishell *minishell)
{
	if (open_outfile(minishell) == -1)
	{
		
		return (-1);
	}
	if (dup2(minishell->cmd_current->infd) == -1)
		return(-1);

}

static int	redirect_input(t_minishell *minishell)
{
	if (open_infile(minishell) == -1)
		return (-1);
	if (dup2(minishell->cmd_current->infd, STDIN_FILENO) == -1)
	{
		// clean up and return error.
		return (-1);
	}
}

void	run_child(t_minishell *minishell)
{
	if (redirect_output(minishell) == -1)
		error_and_exit("failed to redirect the outfile", minishell);
	if (redirect_input(	) == -1)
		eror_and_exit("failed to redirect the infile", minishell);
	if (exec_builtin());
	execute_child();
	perror();
	clean_up_child(minishell);
	exit(127);
	
	// if there is an outfile or infile. Handle_redirects
	// else if no redirects and there is a pipe handle pipe redirects. 
	
}
