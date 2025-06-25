/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:41:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/25 15:28:17 by rgoossen      ########   odam.nl         */
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

# define UNMATCHED_QUOTES_ERR "minishell: unexpected EOF while looking for matching quote\n"
# define MINISHELL_PROMPT "minishell: ~$"

# define ERR_MSG_NL "minishell: syntax error near unexpected token `newline'\n"
# define ERR_MSG_REIN "minishell: syntax error near unexpected token `<'\n"
# define ERR_MSG_REOUT "minishell: syntax error near unexpected token `>'\n"
# define ERR_MSG_HEREDOC "minishell: syntax error near unexpected token `<<'\n"
# define ERR_MSG_REAPPEND "minishell: syntax error near unexpected token `>>'\n"
# define ERR_MSG_PIPE "minishell: syntax error near unexpected token `|'\n"

extern volatile sig_atomic_t g_heredoc_interrupted;

typedef enum e_syntax_err
{
	ERR_NL,
	ERR_REIN,
	ERR_REOUT,
	ERR_HEREDOC,
	ERR_REAPPEND
} t_syntax_err;

typedef enum e_pipe_end
{
	READ_END,
	WRITE_END
} t_pipe_end;

typedef	enum e_signal_locations
{
	main_shell,
	heredoc,
	child_process,
	waiting_parent
} t_signal_locations;

typedef enum e_token_type
{
	WORD,
	RE_OUT,
	RE_IN,
	PIPE,
	RE_APPEND,
	HERE_DOC	
} t_token_type;

typedef struct	s_child_p
{
	int		pid;
	struct	s_child_p *next;
	
} t_child_p;

typedef struct  s_token
{
	t_token_type	type;
	int				len;
	int				start;
	int				end;
	char			quote_flag;
} t_token;

typedef struct s_envp
{
	char *value;
	struct s_envp *next;
} t_envp;

typedef struct s_cmd_table
{
	char					**cmd;
	char					*infile;
	char					*outfile;
	int						infd;
	int						outfd;
	int						append_flag;
	char					*heredoc_delim;
	struct s_cmd_table		*next;

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
	bool	encountered_heredoc;
	
} t_expansion;

typedef struct s_minishells
{
	int			exit_code;
	char		*input;
	char		*pwd;
	pid_t		main_process_pid;
	t_envp		*envp;
	t_cmd_table *cmd_head;
	t_cmd_table *cmd_current;
	t_child_p	*child;
	
} t_minishell;

typedef struct s_parsing
{
	t_minishell	*minishell;
	t_cmd_table	*cmd_table;
	t_cmd_table	*head;
	t_cmd_table	*current;
	t_token		*token;
	t_token		*previous_token;
	int			index;
	char		*temp_file;
	char		*parser_error;
	bool		heredoc_expand;
	
}	t_parsing;

typedef struct s_lexing
{
	t_token_type	type;
	int				len;
	int				start;
	//int				heredoc_flag;
	//int				append_flag;
	//int				expan_flag;
	char			quote_flag;
	char			*value;
	struct s_lexing	*next;
	struct s_lexing *previous;
	t_syntax_err	syntax_err;

} t_lexing;

/* error/ */
void	error_and_exit(char *msg, t_minishell *minishell);

/* get/ */
void	get_envp(t_minishell *minishell, char *envp[]);
void	get_pwd(t_minishell *minishell);

/* init/ */
void	init_minishell(t_minishell *minishell, char *envp[]);
void	init_token(t_token *token, int i);
int		init_parsing(t_minishell *minishell, t_parsing *p);

/* signals/ */
void	handle_signals(t_minishell *minishell, int loc);

/* parser/ */
int				parser(t_minishell *minishell);
int				add_command(t_parsing *p, char *input);
int				add_pipe(t_parsing *p);
int				add_redirect(t_parsing *p, char *input);
int				handle_heredoc(t_parsing *p, char *delimiter);
int				open_file(t_parsing *p, char *file);
void			skip_whitespaces(char *input, int *index);
t_token_type 	get_token_type(char * input, t_token *token);	
void			get_token(t_parsing *p, char *input);


/* epansion */
int			append_char(t_minishell *minishell, t_expansion *expan, char c);
int			append_exit_code(t_minishell *minishell, t_expansion *expan, int *i);
int			append_variable(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i);
void		check_quotes(char c, char *quote_flag);
int			expand_input(t_minishell *minishell);
int			append_heredoc(char *input, t_expansion *expan, int *i);

/* free/ */
void	free_expansion(t_expansion *expan);
void	free_parsing(t_parsing *parsing);

int		purge_quotes(t_parsing *p, char **str);

/* set signals/ */
void	set_signal_protocal(t_minishell *minishell, int location);

/* signal_handlers */
void	handle_shell_signals(int signal, siginfo_t *info, void *ucontext);
void	handle_heredoc_signals(int signal, siginfo_t *info, void *ucontext);
void	handle_child_signals(int signal, siginfo_t *info, void *ucontext);

/* syntax */
int			lexical_parser(t_minishell *mshell);
int			syntax_check(char *input, t_lexing *token_list);
t_lexing	*tokenizer(char *input);
int			get_substrings(char *input, t_minishell *mshell, t_lexing *tokens);

#endif