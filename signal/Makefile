# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 23:29:42 by tkirihar          #+#    #+#              #
#    Updated: 2022/02/11 23:53:20 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= libsignal.a

SRCDIR 	:= ./src/
SRCNAME	:=

SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
INC		:= -I ../includes/
RM		:= rm -rf
LDFLAGS := -Llib/ft_printf -Llib/gnl -Llib/libft -Llib/ft_list
LIBS 	:= -lftprintf -lgnl -lft -llst

HEADERS	:=	. \
			../ \
			./includes/ \
			../libft/ \
			../environ/ \
			../error_handle/ \
			../self_cmd/ \
			../command/ \

INCLUDES	=	$(addprefix -I, $(HEADERS))

all:  $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) ${OBJS}

$(OBJSDIR)%.o : $(SRCDIR)%.c
	${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re