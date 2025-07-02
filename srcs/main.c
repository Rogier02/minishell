/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:30:13 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/21 23:59:09 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void		print_cmd_table(t_cmd_table *cmd_table)
// {
// 	int i;

// 	printf("\n--- Parsed Command Table ---\n");
//    while (cmd_table)
//    {
//        printf("Command:\n");
//        if (cmd_table->cmd)
//        {
//            i = 0;
//            while (cmd_table->cmd[i])
//            {
//                printf("  string[%d]: %s\n", i, cmd_table->cmd[i]);
//                i++;
//            }
//        }
//        else
//            printf("  No command found.\n");

//        if (cmd_table->infile)
//            printf("  Input File: %s\n", cmd_table->infile);
//        else
//            printf("  Input File: None\n");

//         if (cmd_table->outfile)
//             printf("  Output File: %s\n", cmd_table->outfile);
//         else
//             printf("  Output File: None\n");
// 		if (cmd_table->append_flag == 0)
// 			printf("  Append_flag: %i\n", cmd_table->append_flag);
// 		else 
// 			printf("  Append_flag: 1\n");
			
//        printf("  Append Mode: %s\n", cmd_table->heredoc_delim ? "Yes" : "No");

//        if (cmd_table->heredoc_delim)
//            printf("  Heredoc Delimiter: %s\n", cmd_table->heredoc_delim);
//        else
//            printf("  Heredoc Delimiter: None\n");

//        printf("  Input FD: %d\n", cmd_table->infd);
//        printf("  Output FD: %d\n", cmd_table->outfd);

//         cmd_table = cmd_table->next;
//         if (cmd_table)
//             printf("\n--- Next Command ---\n");
//     }
// 	printf("--- End of Command Table ---\n");
// }

//static void	test_executor_out_redir(t_minishell *minishell)
//{
//    t_cmd_table *cmd1 = calloc(1, sizeof(t_cmd_table));

//    // Command: ls > out.txt
//    cmd1->cmd = calloc(2, sizeof(char *));
//    cmd1->cmd[0] = strdup("ls");
//    cmd1->cmd[1] = NULL;
//    cmd1->outfile = strdup("out.txt");
//    cmd1->append_flag = 0; // 0 for >, 1 for >>

//    cmd1->next = NULL;

//    minishell->cmd_table = cmd1;

//    executor(minishell);
//}

//static void	test_executor_in_redir(t_minishell *minishell)
//{
//    t_cmd_table *cmd1 = calloc(1, sizeof(t_cmd_table));

//    // Command: cat < in.txt
//    cmd1->cmd = calloc(2, sizeof(char *));
//    cmd1->cmd[0] = strdup("cat");
//    cmd1->cmd[1] = NULL;
//    cmd1->infile = strdup("in.txt");

//    cmd1->next = NULL;

//    minishell->cmd_table = cmd1;

//    executor(minishell);
//}

//static void	test_executor_in_out_redir(t_minishell *minishell)
//{
//    t_cmd_table *cmd1 = calloc(1, sizeof(t_cmd_table));

//    // Command: cat < in.txt > out.txt
//    cmd1->cmd = calloc(2, sizeof(char *));
//    cmd1->cmd[0] = strdup("cat");
//    cmd1->cmd[1] = NULL;
//    cmd1->infile = strdup("in.txt");
//    cmd1->outfile = strdup("out.txt");
//    cmd1->append_flag = 0;

//    cmd1->next = NULL;

//    minishell->cmd_table = cmd1;

//    executor(minishell);
//}

//static void	test_executor_pipe_redir(t_minishell *minishell)
//{
//    t_cmd_table *cmd1 = calloc(1, sizeof(t_cmd_table));
//    t_cmd_table *cmd2 = calloc(1, sizeof(t_cmd_table));

//    // Command 1: cat < in.txt
//    cmd1->cmd = calloc(2, sizeof(char *));
//    cmd1->cmd[0] = strdup("cat");
//    cmd1->cmd[1] = NULL;
//    cmd1->infile = strdup("in.txt");
//    cmd1->next = cmd2;

//    // Command 2: grep foo > out.txt
//    cmd2->cmd = calloc(3, sizeof(char *));
//    cmd2->cmd[0] = strdup("grep");
//    cmd2->cmd[1] = strdup("foo");
//    cmd2->cmd[2] = NULL;
//    cmd2->outfile = strdup("out.txt");
//    cmd2->append_flag = 0;
//    cmd2->next = NULL;

//    minishell->cmd_table = cmd1;

//    executor(minishell);
//}

//static void	test_executor(t_minishell *minishell)
//{
//    t_cmd_table *cmd1 = calloc(1, sizeof(t_cmd_table));
//    t_cmd_table *cmd2 = calloc(1, sizeof(t_cmd_table));

//    // Command 1: ls
//    cmd1->cmd = calloc(2, sizeof(char *));
//    cmd1->cmd[0] = strdup("ls");
//    cmd1->cmd[1] = NULL;
//    cmd1->next = cmd2;

//    // Command 2: wc -l
//    cmd2->cmd = calloc(3, sizeof(char *));
//    cmd2->cmd[0] = strdup("wc");
//    cmd2->cmd[1] = strdup("-l");
//    cmd2->cmd[2] = NULL;
//    cmd2->next = NULL;

//    minishell->cmd_table = cmd1;

//    executor(minishell);
//}

static int		has_syntax_error(const char *input)
{
	int		i;
	char	quote_flag;

	i = 0;
	quote_flag = '\0';
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
		if (ft_strlen(minishell->input) == 0 && minishell->input != NULL)
			continue ;
		add_history(minishell->input);
		if (has_syntax_error(minishell->input) == 1)
		{
			free(minishell->input);
			continue ;
		}
		if (parser(minishell) == -1)
		{
			free(minishell->input);
			continue ;
		}
		//print_cmd_table(minishell->cmd_table);
		executor(minishell);
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
	//test_executor_out_redir(&minishell);
	//test_executor_in_redir(&minishell);
	//test_executor_in_out_redir(&minishell);
	//test_executor_pipe_redir(&minishell);
	run_minishell(&minishell);
	set_signal_protocal(&minishell, main_shell);
	rl_clear_history();
	//exit_minishell();
}