/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 16:08:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/05 16:08:48 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_parsing(t_parsing *p)
{
	p->cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!p->cmd_table)
		return (-1);
	p->head	= p->cmd_table;
	p->current = p->cmd_table;
	p->index = 0;
	return (0);
}