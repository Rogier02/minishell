/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 14:02:40 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/23 19:13:02 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
checks for the following syntax errors


| Error Type         | Example Input        | Should Error? |
|--------------------|---------------------|:-------------:|
| Pipe at start      | `| ls`              | Yes           |
| Pipe at end        | `ls |`              | Yes           |
| Double pipe        | `ls || ls`          | Yes           |
| Redir at end       | `ls >`              | Yes           |
| Redir at start     | `> file ls`         | **No**        |
| Redir no word      | `ls >   `           | Yes           |
| Redir after redir  | `ls > < file`       | Yes           |
| Heredoc no delim   | `cat <<`            | Yes           |
| Semicolon          | `ls ; ls`           | Yes (for minishell, unless you support `;`) |

**Notes:**
- `> file ls` is valid: it creates/truncates `file` and runs ls with stdout redirected.
- `ls ; ls` is a syntax error in minishell if you do **not** support `;` (as required by most subject PDFs).

*/


static int	check_redir(char *input, t_lexing *token)
{
	char *temp;
	
	if ((token->type == RE_APPEND || token->type == RE_OUT
		|| token->type == RE_IN || token->type == HERE_DOC) 
		&& token->next->type == WORD)
	{
		temp = ft_substr(input, token->next->start, token->next->len);
		if (!temp)
			return (-1);
		if (ft_strncmp("\"\"", temp, 2))
		{
			free(temp);
			return (-1);
		}
	}
	else if ((token->type == RE_APPEND || token->type == RE_OUT
		|| token->type == RE_IN || token->type == HERE_DOC) 
		&& token->next->type != WORD)
	{
		return(-1);	
	}
	free(temp);
	return (0); 
}


int	syntax_check(char *input, t_lexing *token_list)
{
	t_lexing	*current;

	current = token_list;
	while (current)
	{
		if (check_redir(input, current) == -1);
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return (-1);
		}
		if (current->type == PIPE 
			&& (current->previous == NULL || current->next == NULL))
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			//error code sould be 2 if there is a syntax error;
			return (-1);
		}
	}
	return (0);
}
