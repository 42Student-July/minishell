# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/08 10:53:36 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liblst.a

SRCS = ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstsize.c \
			ft_lstnew.c \
			ft_lstdel_front.c \
			ft_lstdel.c \

OBJS = ${SRCS:.c=.o}

CC = gcc 
CFLAGS = -Wall -Werror -Wextra

all: ${LIB_NAME} ${NAME}


$(NAME) : $(OBJS)
	ar rcs ${NAME} ${OBJS}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${OBJS}
re:		fclean all

.PHONY: all clean fclean re .c.o 
