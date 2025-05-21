/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 12:42:12 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/07 17:31:34 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_command(t_parsing *p, char *input)
{
	char *temp;
	char *command_token;
	char **cmd_array;
	
	if (p->token.type == WORD)
	{
		temp = ft_substr(input, p->token.start, p->token.len);
		if (!temp)
			return (-1);
		command_token = purge_quotes(temp);
		if (!command_token)
			return (free(temp), -1);
		if (!p->cmd_table->cmd)
		{
			creat_new_command_array();
			if (!p->cmd_table->cmd)
				return (free(temp), free(command_token), -1);
			return (0);
		}
		else if (add_to_command_table() == -1)
			return (0);
		
	}
	return (0);
}


		//create substring of the token from the input.
		// remove the unnquotes from the input
		// if !new command return -1)
		// if the command table has not been allocated.then malloc.
		// set the new_command string to the command table[0].
		// set command[1] to NULL.
		// free anything than needs to be free'd.