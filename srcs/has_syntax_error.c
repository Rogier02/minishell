/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_syntax_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/09 12:14:54 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:15:15 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_syntax_error(char *input)
{
	int		i;
	char	quote_flag;

	i = 0;
	quote_flag = '\0';
	if (is_only_whitespaces(input))
		return (1);
	while (input[i])
	{
		if (quote_flag == '\0' && (input[i] == '\\' || input[i] == ';'))
			return (1);
		if (quote_flag == '\0'
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = input[i];
		else if (quote_flag == input[i]
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = '\0';
		i++;
	}
	if (quote_flag != '\0')
	{
		ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
