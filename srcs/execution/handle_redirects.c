/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/12 16:13:52 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/12 16:43:56 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output()
{

}

void	redirect_input(t_minishell *minishell)
{

}

int	handle_redirects(t_minishell *minishell)
{
	if (minishell->cmd_current->outfile)
		redirect_output();
	if (minishell->cmd_current->infile)
		redirect_input();
}