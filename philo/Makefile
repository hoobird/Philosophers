CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c
OBJS = $(SRCS:.c=.o)
NAME = philo


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.phony: all fclean clean re philo
