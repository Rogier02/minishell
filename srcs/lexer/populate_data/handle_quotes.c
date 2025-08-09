/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:46:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/09 12:59:58 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_quote_removal(const char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	return (new_str);
}

static int	process_quote_char(const char *str, int i, char *quote_flag)
{
	if (!*quote_flag && (str[i] == '\'' || str[i] == '"'))
	{
		*quote_flag = str[i];
		return (1);
	}
	if (*quote_flag && str[i] == *quote_flag)
	{
		*quote_flag = '\0';
		return (1);
	}
	return (0);
}

static void	copy_char_to_result(char *new_str, int *j, const char *str, int i)
{
	new_str[*j] = str[i];
	(*j)++;
}

char	*remove_valence_quotes(const char *str)
{
	char	*new_str;
	char	quote_flag;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_flag = '\0';
	new_str = init_quote_removal(str);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (process_quote_char(str, i, &quote_flag))
		{
			i++;
			continue ;
		}
		copy_char_to_result(new_str, &j, str, i);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	handle_quotes(t_lexing *token)
{
	char	*temp;

	temp = remove_valence_quotes(token->expanded_value);
	if (!temp)
		return (-1);
	free(token->expanded_value);
	token->expanded_value = temp;
	return (0);
}
