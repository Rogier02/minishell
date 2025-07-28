/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:46:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/06 04:48:21 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	char *remove_quotes(const char *str, int i, int j)
// {
// 	char *new_str;
// 	int	index;
// 	int len;
// 	int	k;

// 	k = 0;
// 	index = 0;
// 	len = ft_strlen(str);
// 	new_str = malloc(len - 1);
// 	if (!new_str)
// 		return (NULL);
// 	while (index < len)
// 	{
// 		if (index != i && index != j)
// 			new_str[k++] = str[index];
// 		index++;
// 	}
// 	new_str[k] = '\0';
// 	return (new_str);
// }

// int	handle_quotes(t_lexing *token)
// {
// 	char	*new_str;
// 	int		len;
// 	int		i;
// 	int		j;
	
// 	len = ft_strlen(token->expanded_value);
// 	i = 0;
// 	while (i < len)
// 	{
// 		if (token->expanded_value[i] == '\'' 
// 			|| token->expanded_value[i] == '\"')
// 		{
// 			token->quote_flag = token->expanded_value[i];
// 			j = len - 1;
// 			while (j > i)
// 			{
// 				if (token->expanded_value[j] == token->quote_flag)
// 				{
// 					new_str = remove_quotes(token->expanded_value, i, j);
// 					if (!new_str)
// 						return (-1);
// 					free(token->expanded_value);
// 					token->expanded_value = new_str;
// 					return (1);
// 				}
// 				j--;
// 			}
// 			break ;
// 		}
// 		i++;		
// 	}
// 	return (0);
// }

char	*remove_valence_quotes(const char *str)
{
    int		len = ft_strlen(str);
    char	*new_str = malloc(len + 1); // new string can't be longer than original
    int		i = 0, j = 0;
    char	quote_flag = '\0';

    if (!new_str)
        return (NULL);

    while (str[i])
    {
        if (!quote_flag && (str[i] == '\'' || str[i] == '"'))
        {
            quote_flag = str[i];
            i++; // skip opening quote
            continue;
        }
        if (quote_flag && str[i] == quote_flag)
        {
            quote_flag = '\0';
            i++; // skip closing quote
            continue;
        }
        new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    return (new_str);
}

int handle_quotes(t_lexing *token)
{
	char	*temp;
	
	temp = remove_valence_quotes(token->expanded_value);
	if (!temp)
		return (-1);
	free(token->expanded_value);
	token->expanded_value = temp;
	return (0);
}
