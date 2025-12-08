#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h" /* or "get_next_line_bonus.h" if you build the bonus */

/* Minimal example: ./gnl_example path/to/file */
int main(int argc, char **argv)
{
	int fd;
	char *line;

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s path/to/file\n", argv[0]);
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); /* get_next_line keeps the trailing newline if present */
		free(line);
	}
	close(fd);
	return 0;
}
