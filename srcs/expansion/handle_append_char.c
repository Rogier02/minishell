/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_append_char.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:18:58 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/01 18:34:23 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char(t_expansion *expan, char c)
{
	char	*new_str;
	int		len;

	if (expan->expanded_input == NULL 
		|| *expan->expanded_input == NULL)
		len = 0;
	else 
		len = ft_strlen(expan->expanded_input);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (-1); 
	if (expan->expanded_input != NULL)
		new_str = ft_memcpy(new_str, expan->expanded_input, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(expan->expanded_input);
	expan->expanded_input = new_str;
	return (0);
}
