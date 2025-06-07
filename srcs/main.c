/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/07 18:50:48 by rgoossen      ########   odam.nl         */
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

static void		print_cmd_table(t_cmd_table *cmd_table)
{
	int i;

    while (cmd_table)
    {
        printf("Command:\n");
        if (cmd_table->cmd)
        {
            i = 0;
            while (cmd_table->cmd[i])
            {
                printf("  string[%d]: %s\n", i, cmd_table->cmd[i]);
                i++;
            }
        }
        else
            printf("  No command found.\n");

        if (cmd_table->infile)
            printf("  Input File: %s\n", cmd_table->infile);
        else
            printf("  Input File: None\n");

        if (cmd_table->outfile)
            printf("  Output File: %s\n", cmd_table->outfile);
        else
            printf("  Output File: None\n");
		if (cmd_table->append_flag == 0)
			printf(" Append_flag: %i\n", cmd_table->append_flag);
		else 
			printf("  Append_flag: 1\n");
			
        printf("  Append Mode: %s\n", cmd_table->heredoc_delim ? "Yes" : "No");

        if (cmd_table->heredoc_delim)
            printf("  Heredoc Delimiter: %s\n", cmd_table->heredoc_delim);
        else
            printf("  Heredoc Delimiter: None\n");

        printf("  Input FD: %d\n", cmd_table->infd);
        printf("  Output FD: %d\n", cmd_table->outfd);

        cmd_table = cmd_table->next;
        if (cmd_table)
            printf("\n--- Next Command ---\n");
    }
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
		printf("\n--- Parsed Command Table ---\n");
        print_cmd_table(minishell->cmd_table);
        printf("--- End of Command Table ---\n");
		// excutiona
		free(minishell->input);
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