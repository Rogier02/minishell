/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 12:33:31 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/25 17:10:39 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file(t_parsing *p, char *file_name)
{
	if (p->cmd_table->outfile)
		free(p->cmd_table->outfile);
	p->cmd_table->outfile = ft_strdup(file_name);
	if (!p->cmd_table->outfile)
	{
		p->parser_error = "malloc failure:";
		return (-1);
	}
}