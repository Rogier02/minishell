/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   advanced_syntax_check.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/22 14:10:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/06/22 19:10:08 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
checks for the following syntax errors

| Error Type         | Example Input        | Should Error?|
|--------------------|----------------------|--------------|
| Pipe at start      | `| ls`               | Yes          |
| Pipe at end        | `ls |`               | Yes          |
| Double pipe        | `ls || ls`           | Yes          |
| Redir at end       | `ls >`               | Yes          |
| Redir at start     | `> file ls`          | Yes          |
| Redir no word      | `ls >   `            | Yes          |
| Redir after redir  | `ls > < file`        | Yes          |
| Heredoc no delim   | `cat <<`             | Yes          |
| Semicolon          | `ls ; ls`            | Yes          |

*/

int	advanced_syntax_check(char *input)
{
	t_lexing	*token_list;

	if (check_semicolon_backslash(input) == -1)
		return (-1);
	token_list = lexical_analysis(input);
	if (token_list == NULL)
	{
		ft_putstr_fd("malloc failure:", STDERR_FILENO);
		return (-1);
	}
	if (syntax_error_check(token_list) == -1)
	{
		ft_putstr_fd("malloc failure:", STDERR_FILENO);
		clean_up_(token_list);
		return (-1);
	}
	clean_up_(token_list);
	return (0);
}