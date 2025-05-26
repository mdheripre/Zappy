##
## EPITECH PROJECT, 2025
## B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
## File description:
## Makefile
##

NAME = zappy_ai

SRC_DIR = src

SRCS = \
	$(SRC_DIR)/main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
