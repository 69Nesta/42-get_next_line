/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:37:44 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/19 14:51:18 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*ft_realloc(char *src, size_t size, size_t add_size);
static size_t	ft_fill_line(char *line, char *buffer, size_t size);
static char		*ft_free_on_fail(char *line);
/*
	
	1. [v] - check if there is an old read if not read
	2. [v] - create new line with a good size
	3. [v] - fill the line
	
	-- loop --
	4. [v] - if i dont find '\n' do a new read
	5. [v] - realloc line
	6. [v] - cat at the end of line
	-- end loop when found '\n'
	
*/

typedef struct s_gnl
{
	ssize_t buffer_index;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
}	t_gnl;

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {
		.buffer = "",
		.buffer_index = 0,
		.bytes_read = 0
	};
	char	*line;
	size_t	line_size;
	size_t	len_to_nl;

	line = NULL;
	line_size = 0;
	while (1)
	{
		if (gnl.buffer_index >= gnl.bytes_read)
		{
			gnl.bytes_read = read(fd, gnl.buffer, BUFFER_SIZE);
			if ((gnl.bytes_read <= 0 && !line) || (gnl.bytes_read < 0 && line))
				return (ft_free_on_fail(line));
			else if (gnl.bytes_read == 0)
				return (line);
			if (gnl.bytes_read < BUFFER_SIZE)
				gnl.buffer[gnl.bytes_read] = 0;
			gnl.buffer_index = 0;
		}
		len_to_nl = ft_strlen_nl(gnl.buffer + gnl.buffer_index, gnl.bytes_read - gnl.buffer_index);
		/*
		__builtin_printf("\n%d | %zu - %zd | %zu\n",
			gnl.buffer[gnl.buffer_index + len_to_nl] == '\n',
			len_to_nl,
			BUFFER_SIZE - gnl.buffer_index,
			line_size
		);*/
		
		line = ft_realloc(line, line_size, len_to_nl + (gnl.buffer[gnl.buffer_index + len_to_nl] == '\n'));
		if (!line)
			return (line);
		line_size += ft_fill_line(line + line_size, gnl.buffer + gnl.buffer_index, len_to_nl);
		if (gnl.buffer[gnl.buffer_index + len_to_nl] == '\n')
		{
			gnl.buffer_index += len_to_nl + 1;
			return (line);
		}
		else
			gnl.buffer_index += len_to_nl;
	}
	return (line);
}

static char	*ft_free_on_fail(char *line)
{
	if (line)
		free(line);
	return (NULL);
}

static size_t	ft_fill_line(char *line, char *buffer, size_t size)
{
	size_t	i;

	i = 0;
	if (!line && size > 0)
		return 0;
	while (i < size)
	{
		line[i] = buffer[i];
		i++;
	}
	// __builtin_printf("Fill: %zu - %zu | %d\n\n", i, size, buffer[size]);
	if (buffer[size] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (i + (buffer[size] == '\n'));
}

static char	*ft_realloc(char *src, size_t size, size_t add_size)
{
	size_t	i;
	char	*new_src;

	i = 0;
	// __builtin_printf("Realloc: %zu - %zu\n", size, add_size);
	new_src = malloc(sizeof(char) * (size + add_size + 1));
	if (!new_src)
	{
		free(src);
		return NULL;
	}
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
