/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:37:44 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/18 16:39:08 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*ft_realloc(char *src, size_t size, size_t add_size);
static size_t	fill_line(char *line, char *buffer);
static char		*ft_free_on_fail(char *line);
/*
	
	1. [v] - check if there is an old read if not read
	2. [x] - create new line with a good size
	3. [x] - fill the line
	
	-- loop --
	4. [x] - if i dont find '\n' do a new read
	5. [x] - realloc line
	6. [x] - cat at the end of line
	-- end loop when found '\n'
	
*/

typedef struct s_gnl
{
	ssize_t buffer_index;
	char	buffer[BUFFER_SIZE];
	ssize_t	read_value;
}	t_gnl;

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {
		.buffer = "",
		.buffer_index = 0,
		.read_value = 0
	};
	char	*line;
	size_t	len_to_nl;
	size_t	line_len;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	if (!gnl.read_value)
		gnl.read_value = read(fd, gnl.buffer, BUFFER_SIZE);
	if (gnl.read_value <= 0)
		return (NULL);
	len_to_nl = ft_strlen_nl(gnl.buffer + gnl.buffer_index, BUFFER_SIZE - gnl.buffer_index);
	line = ft_realloc(0, 0, len_to_nl);
	line_len = fill_line(line, gnl.buffer + gnl.buffer_index);
	if (len_to_nl != (size_t)gnl.read_value)
		gnl.buffer_index += len_to_nl + 1;
	// __builtin_printf("%zd - %zu - %zd - - \n", gnl.buffer_index, len_to_nl, gnl.read_value);
	while (gnl.buffer_index == gnl.read_value + 1)
	{
		gnl.buffer_index = 0;
		gnl.read_value = read(fd, gnl.buffer, BUFFER_SIZE);
		if (gnl.read_value <= 0)
			return (ft_free_on_fail(line));
		len_to_nl = ft_strlen_nl(gnl.buffer, BUFFER_SIZE);
		line = ft_realloc(line, line_len, len_to_nl);
		line_len += fill_line(line, gnl.buffer);
		// __builtin_printf("%zu - - - \n", len_to_nl);
		
	}
	
	return (line);
}

static char	*ft_free_on_fail(char *line)
{
	free(line);
	return (NULL);
}

































// char	*get_next_line(int fd)
// {
// 	static t_gnl	gnl;
// 	char			*line;
// 	size_t			bytes_in_line;
// 	size_t			fill_size;

// 	__builtin_printf("\n");
// 	bytes_in_line = 0;
// 	__builtin_printf("[start] %zu - %zu | %zu\n", gnl.buffer_index, gnl.read_value, bytes_in_line);
// 	if (gnl.read_value == gnl.buffer_index)
// 		gnl.read_value = read(fd, gnl.buffer, BUFFER_SIZE);
// 	if (gnl.read_value == 0)
// 		return (NULL);
// 	line = ft_realloc(0, 0, gnl.read_value - gnl.buffer_index);
// 	fill_size = fill_line(line + bytes_in_line, gnl.buffer + gnl.buffer_index);
// 	gnl.buffer_index += fill_size;
// 	bytes_in_line += fill_size;

// 	__builtin_printf("[ end ] %zu - %zu | %zu\n", gnl.buffer_index , gnl.read_value, bytes_in_line);
// 	while (gnl.buffer_index == gnl.read_value)
// 	{
// 		gnl.buffer_index = 0;
// 		gnl.read_value = read(fd, gnl.buffer, BUFFER_SIZE);
// 		line = ft_realloc(line, bytes_in_line, gnl.read_value);
// 		fill_size = fill_line(line + bytes_in_line, gnl.buffer + gnl.buffer_index);
// 		gnl.buffer_index += fill_size;
// 		bytes_in_line += fill_size;
// 		__builtin_printf("%zu - %zu | %zu\n", gnl.buffer_index, gnl.read_value, bytes_in_line);
// 	}
// 	return (line);
// }

static size_t	fill_line(char *line, char *buffer)
{
	size_t	i;

	i = 0;
	if (!line)
		return 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	line[i + 1] = '\0';
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
