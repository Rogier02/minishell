/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirect.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 15:56:34 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/29 20:07:31 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_append(t_minishell *minishell, t_lexing *token)
{
	if (token->previous->type == RE_APPEND)
	{
		if (minishell->cmd_current->outfile->name)
			free(minishell->cmd_current->outfile->name);
		minishell->cmd_current->outfile->name = \
											ft_strdup(token->expanded_value);
		if (!minishell->cmd_current->outfile->name)
		{
			minishell->exit_code = ENOMEM;
			ft_putstr_fd("malloc failure :\n", 2);
			return (-1);
		}
		minishell->cmd_current->outfile->type_flag == RE_APPEND;
	}
	return (0);
}

static int get_outfile(t_minishell *minishell, t_lexing *token)
{
	if (token->previous->type == RE_OUT)
	{
		if (minishell->cmd_current->outfile->name)
			free(minishell->cmd_current->outfile->name);
		if (!minishell->cmd_current->outfile->name)
		{
			minishell->exit_code = ENOMEM;
			ft_putstr_fd("malloc failure :\n", 2);
			return (-1);
		}
		minishell->cmd_current->outfile->type_flag == RE_OUT;
	}
}

static int get_infile(t_minishell *minishell, t_lexing *token)
{
	if (token->previous->type == RE_IN)
	{
		if (minishell->cmd_current->infile->name)
			free(minishell->cmd_current->infile->name);
		minishell->cmd_current->infile->name = \
											ft_strdup(token->expanded_value);
		if (!minishell->cmd_current->infile->name)
		{
			minishell->exit_code = ENOMEM;
			ft_putstr_fd("malloc failure :\n", 2);
			return (-1);
		}
		minishell->cmd_current->infile->type_flag == RE_IN;
	}	
	return (0);
}

static int get_file_name(t_minishell *minishell, t_lexing *token)
{
	if (get_append(minishell, token) == -1)
		return (-1);
	if (get_outfile(minishell, token) == -1)
		return (-1);
	if (get_infile(minishell, token) == -1)
		return (-1);
	return (0);
}

int	handle_redirect(t_minishell *minishell, t_lexing *token)
{
	if (token->type == is_redirect(token->type))
	{
		token = token->next;
		if (token->type != WORD)
		{
			ft_putstr_fd("should be a syntax error but its not cause you're dumb", 2);
			return (-1);
		}
		if (handle_quotes(token) == -1) // TODO: MIGHT NEED ERROR HANDLING
			return (-1);
		if (handle_heredoc(minishell, token) == -1)
			return (-1);
		if (get_file_name(minishell, token) == -1)
			return (-1);
	}
	return (0);
}