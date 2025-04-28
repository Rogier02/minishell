/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_signals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 17:52:15 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/28 13:18:02 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(t_minishell *minishell, int loc)
{
		struct sigaction	sa;

		ft_memset(&sa, 0, sizeof(sa));
		
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_SIGNINFO;

		
}