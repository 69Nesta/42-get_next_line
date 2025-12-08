*This project has been created as part of the 42 curriculum by rpetit.*

# get_next_line


## Description
This project implements a C function `get_next_line` that reads and returns the next line from a file descriptor, handling arbitrary line lengths and partial reads. It provides a single-FD implementation ([get_next_line.c](get_next_line.c)) and a multi-FD (bonus) implementation ([get_next_line_bonus.c](get_next_line_bonus.c)) that maintains independent state per file descriptor.

Key source files:
- [`get_next_line`](get_next_line.c)
- [`get_next_line.c`](get_next_line.c)
- [`get_next_line_utils.c`](get_next_line_utils.c) (helpers: [`ft_realloc`](get_next_line_utils.c), [`ft_fill_line`](get_next_line_utils.c), [`ft_strlen_nl`](get_next_line_utils.c))
- Bonus: [`get_next_line_bonus.c`](get_next_line_bonus.c), [`get_next_line_utils_bonus.c`](get_next_line_utils_bonus.c)
- Headers: [`get_next_line.h`](get_next_line.h), [`get_next_line_bonus.h`](get_next_line_bonus.h)


## Instructions

### Compile the basic version:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c main.c -o gnl.out
```

### Compile the bonus (multi-FD) version:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 -D FD_MAX=128 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus.out
```

### Run:
```sh
./gnl.out path/to/file.txt
# or for bonus
./gnl_bonus.out path/to/file.txt
```

Adjust `BUFFER_SIZE` at compile time with `-D BUFFER_SIZE=<n>` to test different buffer sizes. 

Optional: you may also adjust `FD_MAX` for the bonus build with `-D FD_MAX=<n>` to change the maximum number of tracked file descriptors. These adjustments are optional and intended for testing different scenarios (large/small buffers, more FDs).


## Algorithm and implementation details

The implementation reads from the file descriptor in chunks of size `BUFFER_SIZE` using `read`. It stores chunk data in a static buffer struct `t_gnl` that contains:

- `buffer` : raw bytes read,
- `bytes_read` : number of valid bytes in buffer,
- `buffer_index` : current read position within the buffer.


### Flow per call to get_next_line:

1. If the internal buffer has been fully consumed, call `read(fd, buffer, BUFFER_SIZE)` to refill it.
2. Locate the next newline (or end of available bytes) using `ft_strlen_nl`.
3. Reallocate the output line buffer using `ft_realloc` to append the new segment.
4. Copy bytes into the line with `ft_fill_line`, append a terminating `\0`, and stop when a newline is found.
5. For the bonus implementation, maintain an array `static t_gnl gnl[FD_MAX]` so each FD keeps its own buffer state.


### Complexity:

- Time: linear in the number of bytes read and copied; each byte is processed a bounded number of times.
- Memory: grows only for the returned line; internal buffers are fixed-size `BUFFER_SIZE` per FD.


### Design choices and justification:

- Static per-FD buffer avoids re-reading bytes already fetched from the OS and allows efficient handling of lines spanning multiple reads.
- The helper functions separate concerns: searching for newline, resizing the line, and copying bytes — simplifying correctness and testing.
- Bonus uses a fixed `FD_MAX` array to remain simple and portable for the project constraints; it avoids dynamic maps and keeps behavior predictable.


## Resources

- POSIX [read(2)](https://man7.org/linux/man-pages/man2/read.2.html) manual.
- POSIX [write(2)](https://man7.org/linux/man-pages/man2/write.2.html) manual.
- POSIX [malloc(3)](https://man7.org/linux/man-pages/man3/free.3.html) manual.
- POSIX [free(3p)](https://man7.org/linux/man-pages/man3/free.3p.html) manual.
- [42 School subject](https://cdn.intra.42.fr/pdf/pdf/188992/en.subject.pdf) and C standard library docs.


### AI usage

AI assistance (GitHub Copilot) was used to help draft the README text.


## Files of interest
- [`get_next_line.c`](get_next_line.c)
- [`get_next_line_utils.c`](get_next_line_utils.c)
- [`get_next_line.h`](get_next_line.h)
- [`get_next_line_bonus.c`](get_next_line_bonus.c)
- [`get_next_line_utils_bonus.c`](get_next_line_utils_bonus.c)
- [`get_next_line_bonus.h`](get_next_line_utils.h)