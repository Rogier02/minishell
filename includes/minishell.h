/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:41:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/30 16:13:01 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ================================ INCLUDES ================================ */

# include "../libft/incl/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/* ================================ DEFINES ================================= */

# define UNMATCHED_QUOTES_ERR \
	"minishell: unexpected EOF while looking \
for matching quote\n"
# define MINISHELL_PROMPT "minishell: ~$"

# define ERR_MSG_NL "minishell: syntax error near unexpected token `newline'\n"
# define ERR_MSG_REIN "minishell: syntax error near unexpected token `<'\n"
# define ERR_MSG_REOUT "minishell: syntax error near unexpected token `>'\n"
# define ERR_MSG_HEREDOC "minishell: syntax error near unexpected token `<<'\n"
# define ERR_MSG_REAPPEND "minishell: syntax error near unexpected token `>>'\n"
# define ERR_MSG_PIPE "minishell: syntax error near unexpected token `|'\n"

# define DEFAULT 0
# define O_FAILURE -1
# define O_SUCCESS 2

# define CHILD_PROCESS 0
# define FORK_FAILURE -1

/* ================================ GLOBALS ================================= */

extern volatile sig_atomic_t	g_heredoc_interrupted;

/* ================================= ENUMS ================================== */

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
	waiting_parent,
	execution
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

/* ================================ STRUCTS ================================= */

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
	char			*value;
	char			*key;
	struct s_envp	*next;
} t_envp;

typedef struct s_file_type
{
	char	*name;
	int		type_flag;
} t_file_type;

typedef struct s_cmd_table
{
	char					**cmd;
	char					*heredoc_delim;
	t_file_type				*infile;
	t_file_type				*outfile;
	int						infd;
	int						outfd;
	struct s_cmd_table		*next;
} t_cmd_table;

typedef struct s_expansion
{
	char	*expanded_input;
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
	int			original_stdout;
	int			original_stdin;
	int			execution_status;
	int			pipe_fd[2];
	char		*pwd;
	char		*input;
	t_envp		*envp;
	t_cmd_table *cmd_head;
	t_cmd_table *cmd_current;
	t_child_p	*child;
} t_minishell;

typedef struct s_lexing
{
	t_token_type	type;
	int				len;
	int				start;
	char			quote_flag;
	char			*value;
	char			*expanded_value;
	struct s_lexing	*next;
	struct s_lexing *previous;
	bool			contains_quotes;
	t_syntax_err	syntax_err;
} t_lexing;

/* ========================== FUNCTION DECLARATIONS ======================== */

/* -------------------------------- BUILTIN -------------------------------- */
int		ft_cd(t_minishell *minishell, char **args);
int		ft_echo(char **args);
int		ft_env(t_minishell *minishell, char **args);
int		ft_exit(t_minishell *minishell, char **args);
int		export_update(t_envp *env, char *key, char *value);
void	ft_export_print(t_envp *env);
int		ft_export(t_minishell *minishell, char **args);
int		ft_pwd(void);
int		ft_unset(t_minishell *minishell, char **args);

/* --------------------------------- ERROR --------------------------------- */
void	error_and_exit(char *msg, t_minishell *minishell);
int		error_malloc_failure(t_minishell *minishell);

/* ------------------------------- EXECUTION ------------------------------- */
int		check_for_builtins(t_minishell *minishell);
int		exec_builtin(t_minishell *minishell);
int		exec_single_builtin(t_minishell *minishell);
void	execute_externals_and_pipes(t_minishell *minishell, int *pid);
int		executor(t_minishell *minishell);
int		exit_child(t_minishell *minishell, int exit_code);
int		open_infile(t_minishell *minishell);
int		open_outfile(t_minishell *minishell);
void	redirect_pipes(t_minishell *minishell);
int		restore_std(t_minishell *minishell);
void	run_child(t_minishell *minishell);
void	wachter(t_minishell *minishell);

/* ------------------------------- PATH UTILS ------------------------------ */
char	**env_list_to_array(t_envp *envp);
char	*find_cmd_path(char *cmd, t_envp *envp);

/* --------------------------------- FREE ---------------------------------- */
int		close_and_reset_fd(int *fd);
int		close_fds(int count, ...);
void	free_cmd_table(t_cmd_table *cmd_table);
void	free_expansion(t_expansion *expan);
void	free_minishell(t_minishell *minishell);
void	recess(t_child_p *child);
void	kill_all_children(t_minishell *minishell);

/* --------------------------------- INIT ---------------------------------- */
void	get_envp(t_minishell *minishell, char *envp[]);
char	*get_pwd(t_minishell *minishell);
void	init_minishell(t_minishell *minishell, char *envp[]);
void	init_token(t_token *token, int i);
void 	init_fds(t_cmd_table *cmd_table);

/* -------------------------------- LEXER ----------------------------------- */
/* Lexical Parser */
void			clean_up_(t_lexing *head);
int				lexical_parser(t_minishell *minishell);
void			print_token_list(t_lexing *token_list, char *input);
void			print_token_values(t_lexing *token_list, int loc);
void			skip_whitespaces(char *input, int *index);
int				is_only_whitespaces(char *input);

/* Tokenizer */
t_lexing		*get_next_token(char *input, int *i);
t_token_type	get_type(char *input, t_lexing *token);
int				is_delimiter(char c);
int				is_redirect(t_token_type type);
int				is_redirect_or_pipe(t_token_type type);
t_lexing		*tokenizer(char *input);

/* Populate Data */
int				handle_command(t_minishell *minishell, t_lexing *token);
int				handle_heredoc(t_minishell *minishell, t_lexing *token);
int				handle_pipe(t_minishell *minishell, t_lexing *token);
int				handle_quotes(t_lexing *token);
int				handle_redirect(t_minishell *minishell, t_lexing *token);
void			init_fds(t_cmd_table *cmd_table);
int				populate_command_data(t_minishell *minishell, t_lexing *token_list);
int				add_heredoc(t_minishell *minishell, char *heredoc_file, int heredoc_fd);

/* Populate Data > Handle Heredoc*/
int			append_line_to_file(int heredoc_fd, char *expanded_line);
char		*expand_heredoc(t_minishell *minishell, char *line);
int			heredoc_append_variable(t_minishell *minishell, t_expansion *expan, char *line, int *i);
int			heredoc_append_exit_code(t_minishell *minishell, t_expansion *expan, char *line, int *i);
int			heredoc_append_char(t_minishell *minishell, t_expansion *expan, char c);
int 		field_split_add(t_minishell *minishell, t_lexing *token);

/* Expansion */
int		append_char(t_minishell *minishell, t_expansion *expan, char c);
int		append_exit_code(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i);
int		append_home(t_minishell *minishell, t_expansion *expan);
int		append_oldpwd(t_minishell *minishell, t_expansion *expan);
int		append_pwd(t_minishell *minishell, t_expansion *expan);
int		append_variable(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i);
void	check_quotes(char c, char *quote_flag);
int		expand_variable(t_envp *envp, t_expansion *expan);
int		expansion(t_minishell *minishell, t_lexing *token);
char	*get_variable_name(char *input, char quote_flag, int i);
int		tilde_expansion(t_minishell *minishell, t_expansion *expan, t_lexing *token, int *i);
int		variable_located(t_expansion *expan, t_envp *head);
void	print_envp(t_envp *envp);

/* Substrings */
int		get_substrings(char *input, t_minishell *mshell, t_lexing *tokens);

/* Syntax */
int		syntax_check(char *input, t_lexing *token_list);

/* -------------------------------- SIGNALS --------------------------------- */
void	set_child_signals(void);
void	handle_child_signals(int signal, siginfo_t *info, void *ucontext);
void	handle_heredoc_signals(int signal, siginfo_t *info, void *ucontext);
void	handle_shell_signals(int signal, siginfo_t *info, void *ucontext);
void	heredoc_signals(struct sigaction *sa, t_minishell *minishell);
void	set_signal_protocal(t_minishell *minishell, int location);
void	shell_signals(struct sigaction *sa, t_minishell *minishell);

#endif