/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:41:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/04/25 20:06:07 by rgoossen      ########   odam.nl         */
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

typedef struct s_minishell
{
	int			exit_code;
	char		*input;
	pid_t		main_process_pid;
	t_envp		*envp;
	t_cmd_table	cmd_table;
} t_minishell;

void	init_minishell(t_minishell *minishell, char *envp[]);
void	collect_envp(t_minishell *minishell, char *envp[]);
void	error_and_exit(char *msg, t_minishell *minishell);

#endif