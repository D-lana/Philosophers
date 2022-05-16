NAME		=	philo

SRCS		=	philo.c ph_create_philo.c ph_monitor.c ph_parser_philo.c ph_destroy_pthread_and_mutex.c \

OBJS		=	${SRCS:.c=.o}

LIBDIR		=	libft

LIBFT_LIB	=	$(LIBDIR)/libft.a

LIB			=	-L$(LIBDIR) -lft

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -I

RM			=	rm -f

%.o: %.c	Makefile philo.h
			$(CC) $(CFLAGS)$(LIBDIR) -Iincludes -c $< -o $@

$(NAME):	$(LIBFT_LIB) $(OBJS)
			@ $(CC) $(CFLAGS)$(LIBDIR) $(OBJS) -o $(NAME) $(LIB)

all:		$(NAME)

$(LIBFT_LIB):	tools ;

tools:
			make -C $(LIBDIR)

clean:		
			make clean -C $(LIBDIR)
			$(RM) $(OBJS)

fclean:		clean 
			make fclean -C $(LIBDIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re tools