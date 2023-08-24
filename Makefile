SRCS	=	main.c \
			check_error.c\
			create_data.c\
			ft_atoi.c\
			ft_calloc.c\
			free.c\
			philo_start_eat.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	philosophers

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

clean:	
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re