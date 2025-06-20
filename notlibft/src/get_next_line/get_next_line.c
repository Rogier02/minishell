/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 15:51:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/24 20:43:05 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remainder(char *buffer)
{
	char	*remainder;
	size_t	i;
	size_t	j;

	remainder = NULL;
	i = gnl_ft_strchr(buffer, '\n');
	j = gnl_ft_strchr(buffer, '\0');
	if (i < 1)
		return (gnl_ft_strdup(""));
	remainder = gnl_ft_substr(buffer, i, j - i);
	if (!remainder)
		return (NULL);
	return (remainder);
}

char	*read_line(char *buffer)
{
	char	*line;
	size_t	j;

	j = gnl_ft_strchr(buffer, '\n');
	if (j < 1)
		j = gnl_ft_strchr(buffer, '\0');
	line = gnl_ft_substr(buffer, 0, j);
	if (!line)
		return (NULL);
	return (line);
}

void	*add_to_buffer(int fd, char *temp, char **remainder, ssize_t bytes_read)
{
	char	*old_remainder;

	while (bytes_read > 0 && (!gnl_ft_strchr(*remainder, '\n')))
	{
		old_remainder = *remainder;
		bytes_read = read(fd, temp, BUFFER_SIZE);
		temp[bytes_read] = '\0';
		*remainder = gnl_ft_strjoin(*remainder, temp);
		if (!*remainder)
			return (gnl_ft_free(&old_remainder), NULL);
		if (gnl_ft_strchr(*remainder, '\n'))
			return (gnl_ft_free(&old_remainder), *remainder);
		gnl_ft_free(&old_remainder);
	}
	return (*remainder);
}

char	*init_buffer(int fd, char **remainder)
{
	char	*temp;
	char	*old_remainder;
	ssize_t	bytes_read;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read < 0)
		return (gnl_ft_free(&temp), NULL);
	if (bytes_read < 1 && !gnl_ft_strchr(*remainder, '\0'))
		return (gnl_ft_free(&temp), NULL);
	if (bytes_read < 1 && *remainder)
		return (gnl_ft_free(&temp), *remainder);
	temp[bytes_read] = '\0';
	old_remainder = *remainder;
	*remainder = gnl_ft_strjoin(*remainder, temp);
	if (!*remainder)
		return (gnl_ft_free(&old_remainder), free(temp), NULL);
	free(old_remainder);
	if (bytes_read > 0 && (!gnl_ft_strchr(*remainder, '\n')))
		add_to_buffer(fd, temp, remainder, bytes_read);
	return (free(temp), *remainder);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder == NULL)
		remainder = gnl_ft_strdup("");
	if (!remainder)
		return (NULL);
	buffer = init_buffer(fd, &remainder);
	if (!buffer)
		return (gnl_ft_free(&remainder), NULL);
	if (!gnl_ft_strchr(buffer, '\n'))
	{
		line = read_line(buffer);
		return (gnl_ft_free(&remainder), line);
	}
	line = read_line(buffer);
	if (!line)
		return (gnl_ft_free(&remainder), NULL);
	remainder = get_remainder(buffer);
	if (!remainder)
		return (gnl_ft_free(&buffer), gnl_ft_free(&line), NULL);
	return (gnl_ft_free(&buffer), line);
}

// int main(void)
// {
// 	int fd;
// 	// char *line;
// 	// fd = open("textfiles/41_no_nl", O_RDONLY);
//  	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/41_with_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/42_no_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/42_with_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/43_no_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/43_with_nl", O_RDONLY);
// 	// printf("main: %s", get_next_line(fd));
// 	// fd = open("textfiles/alternate_line_no_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/alternateK_line_with_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/big_line_with_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/big_line_no_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/empty", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/multiple_line_no_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/multiple_line_with_nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/multiple_nlx5", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	// fd = open("textfiles/nl", O_RDONLY);
// 	// printf("%s", get_next_line(fd));
// 	fd = open("textfiles/text_file.text", O_RDONLY);
// 	char *line;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	// printf("%s", get_next_line(fd));
// 	// read(fd, line, 1000);
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// get_next_line(fd);a
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// get_next_line(fd);s
// 	// line = get_next_line(fd);
// 	// read(fd, mline, 1000);
// 	// printf("%s\n", mline);
// 	// char *line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
//  	// printf("second %s\n", get_next_line(fd));
//  	//  printf("%s", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
//  	// printf("%s\n", get_next_line(fd));
//  	// printf("%s\n", get_next_line(fd));
//  	// printf("%s\n", get_next_line(fd));
//  	// get_next_line(fd);
//  }