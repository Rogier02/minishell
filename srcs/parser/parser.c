/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/23 16:49:02 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_file_token(t_parsing *p, t_token_type type)
{
	char	*file_name;

	file_name = get_file_name();
	if (!file_name)
	{
		p->parser_error = "malloc error:";
		return (-1);
	}
	if (open_file(p, file_name) == -1)
	{
		return (-1);
	}

}


t_cmd_table *parse_input(t_parsing *p, char *input)
{
	while(input[p->index])
	{
		p->token = get_token(p, input);
		if (add_command(p, input) == -1);
				return (-1);
		if (add_node(p, input) == -1)
				return (-1);
		if (p->token.type == RE_APPEND || p->token.type == RE_IN
			|| p->token.type == RE_OUT || p->token.type == HERE_DOC)
		{
			if (add_redirect(p, input) == -1)
				return (-1);
		}
	} 
	return (p->cmd_table);
}

int	parser(t_minishell *minishell)
{
	t_parsing	*parsing;

	if (init_parsing(parsing) == -1)
	{
		minishell->exit_code = ENOMEM;
		return (-1);
	}
	minishell->cmd_table = parse_input(parsing, minishell->input);
	if (!minishell->cmd_table) // ?
	{
		free_parsing(parsing);
		ft_putstr_fd(parsing->parser_error, STDERR_FILENO);
		return (-1);
	}
	return(0);
}

//  char *test_input = "\'$PWD\'";
// 	char *expanded_input;

// 	expanded_input = expand_input(minishell, test_input);
// 	printf("%s\n", expanded_input);