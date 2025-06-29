/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:32:35 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 15:37:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexing	*tokenizer(char *input)
{
	int			i;
	t_lexing	*current;
	t_lexing	*head;
	
	i = 0;
	skip_whitespaces(input, &i);
	current = get_next_token(input, &i);
	if (!current)
		return (NULL);
	head = current;
	current->previous = NULL;
	while (input[i])
	{	
		current->next = get_next_token(input, &i);
		if (!current->next)
		{
			return (NULL);
		}
		current->next->previous = current; 
		current = current->next;
	}
	return (head);
}
