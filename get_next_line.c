/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:37:44 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/18 14:55:45 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_realloc(char *src, size_t size, size_t add_size);
static size_t	fill_line(char *line, char *buffer);
/*
	
	1. [v] - check if there is an old read
	2. [v] - create new line with a good size
	3. [v] - fill the line
	
	-- loop --
	4. [x] - if i dont find '\n' do a new read
	5. [x] - realloc line
	6. [x] - cat at the end of line
	-- end loop when found '\n'
	
*/

char	*get_next_line(int fd)
{
	static ssize_t	buffer_i = 0;
	static char		buffer[BUFFER_SIZE] = "";
	static ssize_t	read_value = 0;
	char			*line;
	size_t			bytes_in_line;
	size_t			fill_size;

	__builtin_printf("\n");
	bytes_in_line = 0;
	__builtin_printf("[start] %zu - %zu | %zu\n", buffer_i, read_value, bytes_in_line);
	if (read_value == buffer_i)
		read_value = read(fd, buffer, BUFFER_SIZE);
	if (read_value == 0)
		return (NULL);
	line = ft_realloc(0, 0, read_value - buffer_i);
	fill_size = fill_line(line + bytes_in_line, buffer + buffer_i);
	buffer_i += fill_size;
	bytes_in_line += fill_size;

	__builtin_printf("[ end ] %zu - %zu | %zu\n", buffer_i, read_value, bytes_in_line);
	while (buffer_i == read_value)
	{
		buffer_i = 0;
		read_value = read(fd, buffer, BUFFER_SIZE);
		line = ft_realloc(line, bytes_in_line, read_value);
		fill_size = fill_line(line + bytes_in_line, buffer + buffer_i);
		buffer_i += fill_size;
		bytes_in_line += fill_size;
		__builtin_printf("%zu - %zu | %zu\n", buffer_i, read_value, bytes_in_line);
	}
	return (line);
}

static size_t	fill_line(char *line, char *buffer)
{
	size_t	i;

	i = 0;
	if (!line)
		return 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		i++;
		if (buffer[i] == '\n')
			break ;
	}
	line[i] = '\0';
	return (i + (buffer[i] == '\n'));
}

static char	*ft_realloc(char *src, size_t size, size_t add_size)
{
	size_t	i;
	char	*new_src;

	i = 0;
	new_src = malloc(sizeof(char) * (size + add_size + 1));
	if (!new_src)
		return NULL;
	while (i < size)
	{
		new_src[i] = src[i];
		i++;
	}
	if (size > 0)
		free(src);
	new_src[i] = '\0';
	return (new_src);
}
