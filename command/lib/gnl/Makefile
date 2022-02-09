# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 16:44:44 by mhirabay          #+#    #+#              #
#    Updated: 2022/01/13 22:55:21 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c get_next_line_utils_2.c
OBJS = ${SRCS:.c=.o}

$(NAME) : $(OBJS)
CC = gcc 
CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${OBJS}
re:		fclean all

.PHONY: all clean fclean re .c.o
