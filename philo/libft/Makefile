# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlana <dlana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 21:56:09 by dlana             #+#    #+#              #
#    Updated: 2021/12/18 16:13:02 by dlana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	ft_atoi.c ft_isdigit.c\


OBJS		=	${SRCS:.c=.o}

HEADER		=  -I libft.h

.c.o:		=	libft.h
			${CC} ${CFLAGS} -c $< ${HEADER} -o ${<:.c=.o} 

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}
	
clean:	
			${RM} ${OBJS} 
			
fclean:		clean
			${RM} ${NAME} 

re:			fclean all

.PHONY: all clean fclean re bonus