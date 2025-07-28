/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 15:52:06 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/24 20:40:51 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <bsd/string.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	gnl_ft_strchr(char *str, int c);
char	*get_next_line(int fd);
char	*gnl_ft_strdup(char *str);
char	*gnl_ft_substr(char *str, size_t start, size_t len);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*get_remainder(char *buffer);
char	*read_line(char *buffer);
char	*init_buffer(int fd, char **remainder);
void	gnl_ft_free(char **str);

#endif