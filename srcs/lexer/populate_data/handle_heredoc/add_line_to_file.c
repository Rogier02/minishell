/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_line_to_file.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 19:33:38 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/27 19:47:31 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_line_to_file(int heredoc_fd, char *expanded_line)
{
    if (!expanded_line)
	{
        return (-1);
	}
	write(heredoc_fd, expanded_line, ft_strlen(expanded_line));
	write(heredoc_fd, "\n", 1);
    return (0);
}