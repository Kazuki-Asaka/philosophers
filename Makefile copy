SRCS	=	main.c \
			check_error.c\
			ft_atoi.c\
			ft_calloc.c\
			free.c\
			create_philo_array.c\
			manage_philo.c\
			stop_watch.c\
			sync_barrier.c\
			take_fork.c\
			thinking.c\
			sleeping.c\
			philo_die_check.c\
			mutex_init.c\
			set_data.c\
			destroy_mutex.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	philo

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS)  -lpthread -o $(NAME)

clean:	
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re