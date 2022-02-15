# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/14 18:49:07 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= libcommand.a



SRCDIR 	:= ./src/
SRCNAME	:=	execute_builtin.c \
			execute_self.c \
			execute.c \
			redirect_process.c \
			init.c \
			create_cmd.c \
			convert_lst_to_argv.c \
			no_pipe_process.c \
			pipe_process.c \
			exec_attribute_utils.c \
			$(SELFCMD_SRCS) \


SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
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

INCLUDES	=	$(addprefix -I, $(HEADERS))

all:  $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) ${OBJS}

$(OBJSDIR)%.o : $(SRCDIR)%.c
	mkdir -p $(OBJSDIR)$(ENV_DIR)
	mkdir -p $(OBJSDIR)$(SELFCMD_DIR)
	${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)

fclean: clean
	${RM} ${NAME}
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug lib
