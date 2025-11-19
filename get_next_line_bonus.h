/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:42:59 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/19 17:36:48 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef FD_COUNT
#  define FD_COUNT 10000
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl
{
	ssize_t	buffer_index;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
}	t_gnl;

char	*get_next_line(int fd);

/* Utils */
size_t	ft_strlen_nl(const char *str, size_t size);
char	*ft_realloc(char *src, size_t size, size_t add_size);
size_t	ft_fill_line(char *line, char *buffer, size_t size);
void	ft_stop(int *stop);
void	ft_free_on_fail(char **line, int *stop);

#endif