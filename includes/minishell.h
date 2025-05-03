/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:41:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/05/03 18:07:16 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>

# include <sys/stat.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/incl/libft.h"

# define MINISHELL_PROMPT "minishell: ~$"

typedef struct s_envp
{
	char *value;
	struct s_envp *next;
} t_envp;

typedef struct s_cmd_table
{
	char					**cmd;
	char					*infile;
	char					*outifle;
	int						infd;
	int						outfd;
	int						heredoc;
	char					*heredoc_delim;
	struct s_command_table	*next;

} t_cmd_table;

typedef struct s_expansion
{
	char	*expanded_input;
	char	quote_flag;
	char	*var_name;
	char	*var_expanded;
	int		var_name_len;
	t_envp	*envp_copy;
	int		exit_code_copy;
	
} t_expansion;

typedef struct s_minishells
{
	int			exit_code;
	char		*input;
	char		*pwd;
	pid_t		main_process_pid;
	t_envp		*envp;
	t_cmd_table	*cmd_table;
} t_minishell;

/* error/ */
void	error_and_exit(char *msg, t_minishell *minishell);

/* get/ */
void	get_envp(t_minishell *minishell, char *envp[]);
void	get_pwd(t_minishell *minishell);

/* init/ */
void	init_minishell(t_minishell *minishell, char *envp[]);

/* signals/ */
void	handle_signals(t_minishell *minishell, int loc);

/* parser/ */
int		parser(t_minishell *minishell);

int		append_char(t_expansion *expan, char c);
int		append_exit_code(t_expansion *expan, int *i);
int		append_variable(t_expansion *expan, char *input, int *i);
void	check_for_quotes(char c, t_expansion *expan);
char	*expand(t_minishell *mshell, char *input);

/* free/ */
void	free_expansion(t_expansion *expan);

#endif