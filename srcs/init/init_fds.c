/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_fds.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 14:00:51 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/29 14:01:07 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	init_fds(t_cmd_table *cmd_table)
{
	cmd_table->infd = -1;
	cmd_table->outfd = -1;
}