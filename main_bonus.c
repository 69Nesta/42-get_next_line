/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetit <rpetit@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:48:08 by rpetit            #+#    #+#             */
/*   Updated: 2025/11/19 17:19:59 by rpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	// fd = open("./test_file0.txt", O_RDONLY);
	// fd = open("./test_file_1test_file_1.txt", O_RDONLY);
	// fd = open("./tests/42_no_nl", O_RDONLY);
	// fd = open("./tests/1char.txt", O_RDONLY);
	// fd = open("./tests/multiple_line_no_nl", O_RDONLY);
	fd = open("./tests/read_error.txt", O_RDONLY);
	if (!fd)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		__builtin_printf("'%s'\n-------%d-------\n", line, ft_strlen(line));
		__builtin_printf("'%d'\n\n", line[ft_strlen(line) - 1]);
		free(line);
		i++;
	}
	close(fd);
}
