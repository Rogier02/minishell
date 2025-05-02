/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 19:46:06 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/02 18:34:32 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_quotes(char c, t_expansion *expansion)
{
	if (expansion->quote_flag && (c == '\'' || c == '\"'))
		expansion->quote_flag = c;
	else if (expansion->quote_flag != 0 && c == expansion->quote_flag)
		expansion->quote_flag = 0;
}
