/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:46:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/05 15:46:53 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *remove_quotes(const char *str, int i, int j)
{
	char *new_str;
	int	index;
	int len;
	int	k;

	k = 0;
	index = 0;
	len = ft_strlen(str);
	new_str = malloc(len - 1);
	if (!new_str)
		return (NULL);
	while (index < len)
	{
		if (index != i && index != j)
			new_str[k] = str[index];
		k++;
		index++;
	}
	new_str[k] = '\0';
	return (new_str);
}

int	handle_quotes(t_lexing *token)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;
	
	len = ft_strlen(token->expanded_value);
	i = 0;
	while (i < len)
	{
		if (token->expanded_value[i] == '\'' 
			|| token->expanded_value[i] == '\"')
		{
			token->quote_flag = token->expanded_value[i];
			j = len - 1;
			while (j > i)
			{
				if (token->expanded_value[j] == token->quote_flag)
				{
					new_str = remove_quotes(token->expanded_value, i, j);
					if (!new_str)
						return (-1);
					free(token->expanded_value);
					token->expanded_value = new_str;
					return (1);
				}
				j--;
			}
			break ;
		}
		i++;		
	}
	return (0);
}
