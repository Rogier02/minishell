/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_variable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 13:08:08 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/27 15:44:40 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(t_envp *envp)
{
	t_envp *head;
	
	head = envp;
	while (head)
	{
		printf("%s\n", head->value);
		head = head->next;
	}
}

static int	find_and_expand_variable(t_expansion *expan)
{
    t_envp	*head = expan->envp_copy;

    while (head)
    {
        if (variable_located(expan, head) == 0)
        {
            if (expand_variable(head->value, expan) == -1)
                return (-1);
            break;
        }
        head = head->next;
    }
    if (expan->var_expanded == NULL)
    {
        expan->var_expanded = ft_strdup("");
        if (!expan->var_expanded)
            return (-1);
    }
    return (0);
}

static int	append_expanded_variable(t_expansion *expan)
{
    char *temp = ft_strjoin(expan->expanded_input, expan->var_expanded);
    if (!temp)
        return (-1);
    free(expan->expanded_input);
    expan->expanded_input = temp;
    return (0);
}

int	append_variable(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i)
{
    expan->var_name = get_variable_name(token->value, expan->quote_flag, *i);
    if (!expan->var_name)
        return (-1);
    expan->var_name_len = ft_strlen(expan->var_name);

    if (find_and_expand_variable(expan) == -1)
    {
        minishell->exit_code = ENOMEM;
        return (-1);
    }
    if (append_expanded_variable(expan) == -1)
        return (-1);

    (*i) += expan->var_name_len;
    return (0);
}
