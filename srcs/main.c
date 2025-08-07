/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/08/06 17:13:59 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void		print_cmd_table(t_cmd_table *cmd_table)
// {
// 	int i;
// 	t_cmd_table *temp;

// 	temp = cmd_table;
// 	printf("\n--- Parsed Command Table ---\n");
//    while (temp)
//    {
//        printf("Command:\n");
//        if (temp->cmd)
//        {
//            i = 0;
//            while (temp->cmd[i])
//            {
//                printf("  string[%d]: %s\n", i, temp->cmd[i]);
//                i++;
//            }
//        }
//        else
//            printf("  No command found.\n");

//        if (temp->infile)
//            printf("  Input File: %s\n", temp->infile->name);
//        else
//            printf("  Input File: None\n");

//         if (temp->outfile)
//             printf("  Output File: %s\n", temp->outfile->name);
//         else
//             printf("  Output File: None\n");
// 		if (temp->outfile && temp->outfile->type_flag == RE_APPEND)
// 			printf("  Append_flag: %i\n", temp->outfile->type_flag);
// 		else 
// 			printf("  Append_flag: No\n");
			
//        printf("  Append Mode: %s\n", temp->heredoc_delim ? "Yes" : "No");

//        if (temp->heredoc_delim)
//            printf("  Heredoc Delimiter: %s\n", temp->heredoc_delim);
//        else
//            printf("  Heredoc Delimiter: None\n");

//        printf("  Input FD: %d\n", temp->infd);
//        printf("  Output FD: %d\n", temp->outfd);

//         temp = temp->next;
//         if (temp)
//             printf("\n--- Next Command ---\n");
//     }
// 	printf("--- End of Command Table ---\n");
// }

static int		has_syntax_error(char *input)
{
	int		i;
	char	quote_flag;

	i = 0;
	quote_flag = '\0';
	if (is_only_whitespaces(input))
		return (1);
	while (input[i])
	{	
		if (quote_flag == '\0' && (input[i] == '\\' || input[i] == ';'))
			return (1);
		if (quote_flag == '\0' 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = input[i];
		else if (quote_flag == input[i] 
			&& (input[i] == '\'' || input[i] == '\"'))
			quote_flag = '\0';
		i++;
	}
	if (quote_flag != '\0')
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void		reset_data(t_minishell *minishell)
{
	free_cmd_table(minishell->cmd_head);
	minishell->cmd_head = NULL;
	minishell->cmd_current = NULL;
	minishell->cmd_head = ft_calloc(1, sizeof(t_cmd_table));
	if (!minishell->cmd_head)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current = minishell->cmd_head;
	minishell->cmd_current->infile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->infile)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current->outfile = ft_calloc(1, sizeof(t_file_type));
	if (!minishell->cmd_current->outfile)
	{
		free_minishell(minishell);
		exit(ENOMEM);
	}
	minishell->cmd_current->infd = -1;
	minishell->cmd_current->outfd = -1;
	ft_memset(minishell->pipe_fd, -1, sizeof(int [2]));
}
// static void		sig_resist(t_minishell *minishell)
// {
// 	(void)minishell;
// 	//set_signal_protocal(minishell, main_shell);
// 	// reset_data(minishell);
//     // free(minishell->input);
// 	// //g_heredoc_interrupted = 0;
// 	// write(1, "\n", 1);    
//     // rl_replace_line("", 0);
//     // rl_on_new_line();
// 	// rl_redisplay();
// }
static void		run_minishell(t_minishell *minishell)
{
	int		parse_status;
	
	while (1)
	{
		set_signal_protocal(minishell, main_shell);
		minishell->input = readline("minishell:~$ ");
		if (!minishell->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		} 
		if (ft_strlen(minishell->input) == 0 && minishell->input != NULL)
			continue ;
		add_history(minishell->input);
		if (has_syntax_error(minishell->input) == 1)
		{
			free(minishell->input);
			continue ;
		}
		parse_status = lexical_parser(minishell);
		if (parse_status == 1)
		{
			reset_data(minishell);
			free(minishell->input);
			continue ;
		}
		if (parse_status == -1)
		{
			free_minishell(minishell);
			exit(ENOMEM);
		}
	//	print_cmd_table(minishell->cmd_head);
		if (executor(minishell) == -1)
			ft_putstr_fd("minishell: execution failed\n", STDERR_FILENO);
		reset_data(minishell);
		free(minishell->input);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell minishell;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("Nope\n", 2);
		return (2);
	}
	//handle_signals();
	init_minishell(&minishell, envp);
	set_signal_protocal(&minishell, main_shell);
	run_minishell(&minishell);
	rl_clear_history();
	free_minishell(&minishell);
	return (0);
}