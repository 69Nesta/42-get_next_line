#!/bin/sh -e

cc -Wall -Wextra -Werror -g3 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl.out && valgrind ./gnl.out