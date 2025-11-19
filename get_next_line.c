/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:37:44 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/19 17:24:51 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_read(int fd, t_gnl *gnl, char **line, int *stop);
static void		ft_processes(t_gnl *gnl, char **line, size_t *line_size,
					int *stop);

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {.buffer = "", .buffer_index = 0, .bytes_read = 0};
	char			*line;
	size_t			line_size;
	int				stop;

	stop = 0;
	line = NULL;
	line_size = 0;
	while (!stop)
	{
		ft_read(fd, &gnl, &line, &stop);
		if (!stop)
			ft_processes(&gnl, &line, &line_size, &stop);
	}
	return (line);
}

static void	ft_read(int fd, t_gnl *gnl, char **line, int *stop)
{
	if (gnl->buffer_index >= gnl->bytes_read)
	{
		gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
		if ((gnl->bytes_read <= 0 && !*line) || (gnl->bytes_read < 0 && *line))
		{
			ft_free_on_fail(line, stop);
			return ;
		}
		else if (gnl->bytes_read == 0)
		{
			ft_stop(stop);
			return ;
		}
		if (gnl->bytes_read < BUFFER_SIZE)
			gnl->buffer[gnl->bytes_read] = 0;
		gnl->buffer_index = 0;
	}
}

static void	ft_processes(t_gnl *gnl, char **line, size_t *line_size, int *stop)
{
	size_t	len_to_nl;

	len_to_nl = ft_strlen_nl(gnl->buffer + gnl->buffer_index,
			gnl->bytes_read - gnl->buffer_index);
	*line = ft_realloc(*line, *line_size,
			len_to_nl + (gnl->buffer[gnl->buffer_index + len_to_nl] == '\n'));
	if (!*line)
	{
		ft_free_on_fail(line, stop);
		return ;
	}
	*line_size += ft_fill_line(*line + *line_size,
			gnl->buffer + gnl->buffer_index, len_to_nl);
	if (gnl->buffer[gnl->buffer_index + len_to_nl] == '\n')
	{
		gnl->buffer_index += len_to_nl + 1;
		ft_stop(stop);
		return ;
	}
	else
		gnl->buffer_index += len_to_nl;
}
