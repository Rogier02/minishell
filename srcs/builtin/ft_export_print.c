/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_print.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 12:30:36 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/08 12:17:36 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_print(t_envp *env)
{
	t_envp	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->key, 1);
		if (current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}
