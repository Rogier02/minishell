/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 18:13:23 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/05 17:08:24 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table *parse_input(t_parsing *p, char *input)
{
	while(input[p->index])
	{
		p->token = get_token(p, input);
		if (p->token.type == WORD)
			add_command();
		if (p->token.type == PIPE)
			add_node();
		if (p->token.type == RE_APPEND
			|| p->token.type == RE_IN
			|| p->token.type == RE_OUT
			|| p->token.type == HERE_DOC)
		{
			p->temp_token = p->token;
			p->token = get_token(input, p->token.end);
			if (p->token.type != WORD)
			{
				p->parser_error = ft_substr(input, \
									p->token.start, p->token.len);
				return (NULL);
			}
			handle_file_token();
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