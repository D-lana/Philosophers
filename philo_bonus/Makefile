NAME_B		=	philo_bonus

SRCS_BONUS	=	philo_bonus.c ph_create_philo_bonus.c ph_do_action_bonus.c ph_parser_philo_bonus.c \

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

LIBDIR		=	libft

LIBFT_LIB	=	$(LIBDIR)/libft.a

LIB			=	-L$(LIBDIR) -lft

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -I

RM			=	rm -f

%.o: %.c	Makefile philo_bonus.h
			$(CC) $(CFLAGS)$(LIBDIR) -Iincludes -c $< -o $@

$(NAME_B):	$(LIBFT_LIB) $(OBJS_BONUS)
			@ $(CC) $(CFLAGS)$(LIBDIR) $(OBJS_BONUS) -o $(NAME_B) $(LIB)

all:		$(NAME_B)

bonus:		all

$(LIBFT_LIB):	tools ;

tools:
			make -C $(LIBDIR)

clean:		
			make clean -C $(LIBDIR)
			$(RM) $(OBJS_BONUS)

fclean:		clean 
			make fclean -C $(LIBDIR)
			$(RM) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re tools bonus