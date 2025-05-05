/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/05 13:13:28 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool has_unmatched_quotes(char *input)
{
	char	quote_flag;
	int		i;

	i = 0;
	quote_flag = 0;
	while(input[i])
	{
		if (quote_flag == 0 && (input[i] == '\'' 
								|| input[i] == '\"'))
			quote_flag = input[i];
		else if (quote_flag != 0 && input[i] == quote_flag)
			quote_flag = 0;
		i++;
	}
	return (quote_flag != 0);
}

static char	*get_complete_input(char *initial_input)
{
	char	*new_input;
	char	*temp;

	while (has_unmatched_quotes(initial_input))
	{
		new_input = readline("> ");
		if (!new_input)
		{
			ft_putstr_fd(UNMATCHED_QUOTES_ERR , STDERR_FILENO);
			free(initial_input);
			return (NULL);
		}
		temp = ft_strjoin(initial_input, "\n");
		free(initial_input);
		if (!temp)
			return (free(temp), NULL);
		initial_input = ft_strjoin(temp, new_input);
		free(temp);
		free(new_input);
		if (!initial_input)
			return (NULL);
	}
	return (initial_input);
}

static void		run_minishell(t_minishell *minishell)
{
	while (1)
	{
		minishell->input = readline("minishell:~$ ");
		if (!minishell->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break;
		}
		minishell->input = get_complete_input(minishell->input);
		if (minishell->input[0])
			add_history(minishell->input);
		if (parser(minishell) == -1)
			continue ;
		// initial input check. white spaces, empty line. etc
		// add input to history
		// expand input.
		// parse input
		// execute inpute
		
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell minishell;

	(void)argv;
	if (argc > 1)
	{
		// TODO return simple error to 2.
	}
	//handle_signals();
	init_minishell(&minishell, envp);
	run_minishell(&minishell);
	rl_clear_history();
	//exit_minishell();
}