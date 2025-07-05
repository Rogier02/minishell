/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_table.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/05 18:12:30 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/05 18:12:49 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_file_struct(t_file_type *file)
{
	free(file->name);
	free(file);
}

void		free_cmd_table(t_cmd_table *cmd_table)
{
	int i;
	t_cmd_table *tmp;

	while (cmd_table)
	{
		tmp = cmd_table->next;
        if (cmd_table->cmd)
        {
            i = 0;
            while (cmd_table->cmd[i])
            {
                free(cmd_table->cmd[i]);
                i++;
            }
            free(cmd_table->cmd);
        }
        if (cmd_table->infile)
			free_file_struct(cmd_table->infile);
        if (cmd_table->outfile)
			free_file_struct(cmd_table->outfile);
        if (cmd_table->heredoc_delim)
            free(cmd_table->heredoc_delim);
        free(cmd_table);
        cmd_table = tmp;
	}
}