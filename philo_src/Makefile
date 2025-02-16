CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = philo_main.c philo_utils.c philo_init.c philo_sim.c philo_monitor.c philo_pars.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re