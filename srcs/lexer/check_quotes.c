/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 19:46:06 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/27 16:20:28 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, char *quote_flag)
{
	if (*quote_flag == '\0' && (c == '\'' || c == '\"'))
		*quote_flag = c;
	else if (*quote_flag != '\0' && c == *quote_flag)
		*quote_flag = '\0';
}
