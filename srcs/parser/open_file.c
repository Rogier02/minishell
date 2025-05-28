/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 12:33:31 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/28 17:19:10 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_to_outfile(t_parsing *p, char *file)
{
	if (p->cmd_table->outfile)
		free(p->cmd_table->outfile);
	p->cmd_table->outfile = ft_strdup(file);
	if (!p->cmd_table->outfile)
	{
		p->parser_error = "malloc failure: ";
		return (-1);
	}
	p->cmd_table->outfd = open(p->cmd_table->outfile, \
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->cmd_table->outfd == -1)
	{
		p->parser_error = "open failure: ";
		return (-1);
	}
	return (0);
}

int open_to_infile(t_parsing *p, char *file)
{
	if (p->cmd_table->infile)
		free(p->cmd_table->infile);
	p->cmd_table->infile = ft_strdup(file);
	if (!p->cmd_table->infile)
	{
		p->parser_error = "malloc failure: ";
		return (-1);
	}
	p->cmd_table->infd = open(p->cmd_table->infile, O_RDONLY);
	if (p->cmd_table->infd == -1)
	{
		p->parser_error = "open failure: ";
		return (-1);
	}
	return (0);
}

int open_file(t_parsing *p, char *file)
{
	if (p->previous_token->type == RE_APPEND 
		|| p->previous_token->type == RE_OUT)
	{
		if (open_to_outfile(p, file) == -1)
			return (-1);
	}
	if (p->previous_token->type == RE_IN)
	{
		if (open_to_infile(p, file) == -1)
			return (-1);
	}
	return (0);
}
