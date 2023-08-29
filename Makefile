SRCS	=	main.c \
			check_error.c\
			ft_atoi.c\
			ft_calloc.c\
			free.c\
			create_philo_array.c\
			manage_philo.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	philosophers

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS)  -lpthread -o $(NAME)

clean:	
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re