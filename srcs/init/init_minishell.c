/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minishell.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:34:37 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/24 14:40:39 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minshell(t_minishell *minishell, char *envp[])
{
	
	initialize_signals()
	minishell->envp = collect_envp(envp);
	minsiehll->pwd = collect_pwd(envp);
	
}