/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 16:06:41 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/23 16:11:58 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pipe(t_parsing *p, char *input)
{
	if (p->token.type == PIPE)
	{
		p->cmd_table->next = new_node();
		if (!p->cmd_table->next)
		{
			p->parser_error = "malloc failure:";
			return (-1);
		}
		p->cmd_table = p->cmd_table->next;
	}
}