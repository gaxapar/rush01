NAME	= rush-01
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ex00/main.c ex00/parse.c ex00/check.c ex00/line.c ex00/solve.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c ex00/rush01.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	python3 tests/test.py ./$(NAME)

.PHONY: all clean fclean re test
