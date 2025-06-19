/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/19 19:17:22 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table *parse_input(t_parsing *p, char *input)
{
	while(input[p->index])
	{
		get_token(p, input);
		if (add_command(p, input) == -1)
				return (NULL);
		if (add_pipe(p) == -1)
				return (NULL);
		if (p->token->type == RE_APPEND || p->token->type == RE_IN
			|| p->token->type == RE_OUT || p->token->type == HERE_DOC)
		{
			if (add_redirect(p, input) == -1)
				return (NULL);
		}
	} 
	return (p->cmd_table);
}

int	parser(t_minishell *minishell)
{
	t_parsing	parsing;

	if (expand_input(minishell) == -1)
	{
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	//printf("expanded input %s", minishell->input);
	if (init_parsing(minishell, &parsing) == -1)
	{
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_table = parse_input(&parsing, minishell->input);
	if (!minishell->cmd_table) // ?
	{
		//free_parsing(parsing);
		ft_putstr_fd(parsing.parser_error, STDERR_FILENO);
		return (-1);
	}
	return(0);
}

//  char *test_input = "\'$PWD\'";
// 	char *expanded_input;

// 	expanded_input = expand_input(minishell, test_input);
// 	printf("%s\n", expanded_input);