/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_child.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 14:05:25 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/12 16:13:39 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child(t_minishell *minishell)
{
	if (handle_redirects(minishell) == O_FAILURE)
		error_and_exit("?", minishell);
	exec_builtin();
	
	
	// if there is an outfile or infile. Handle_redirects
	// else if no redirects and there is a pipe handle pipe redirects. 
	
}