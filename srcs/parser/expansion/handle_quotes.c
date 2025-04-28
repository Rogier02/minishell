/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 19:46:06 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/28 20:06:07 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_quotes(char c, t_expansion *expansion)
{
	if (expansion->quote_flag && (c == '\'' || c == '\"'))
		expansion->quote_flag = c;
	else if (expansion->quote_flag != 0 && c == expansion->quote_flag)
		expansion->quote_flag = 0;
	reuturn (0);
}
