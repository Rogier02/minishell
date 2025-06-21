/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/21 15:56:56 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/21 19:05:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*get_delim_len(t_expansion *expan, char *input, int i)
{
	int	len;

	len = 0;
	check_quotes(input[i], expan->quote_flag);
	while (input[i] == ' ' && expan->quote_flag == '\0')
	{
		i++;
		len++;
	}
	while (input[i])
	{
		check_quotes(input[i], expan->quote_flag);
		if (expan->quote_flag == '\0' && input[i] == ' ')
			return (len);
		i++;
		len++;
	}
	return (len);
}

int	append_heredoc(char *input, t_expansion *expan, int *i)
{
	char	*delimiter;
	int		delim_len;
	char	*temp;

	if (input[*i] == '<' && input[*i + 1] == '<' && expan->quote_flag == '\0')
	{
		*i += 2;
		delim_len = get_delim_len(expan, input, i);
		if 
		delimiter = ft_substr(input, i, delim_len);
		if (!delimiter)
			return (-1);
		temp = ft_strjoin(expan->expanded_input, delimiter);
		free(expan->expanded_input);
		expan->expanded_input = temp;
		*i += delim_len;
	}
}