# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/10 14:07:48 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= libcommand.a

SELFCMD_DIR := self_cmd/
SELFCMD_SRCNAME := self_pwd.c \
				self_cd.c \
				self_echo.c \
				self_exit.c \
				self_env.c \
				self_export.c \
				self_export_utils.c \
				self_unset.c \
				self_cmd_utils.c \

SELFCMD_SRCS := $(addprefix $(SELFCMD_DIR), $(SELFCMD_SRCNAME))

SRCDIR 	:= ./src/
SRCNAME	:=	execute_builtin.c \
			execute_self.c \
			execute.c \
			redirect_process.c \
			init.c \
			create_cmd.c \
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
			
INCLUDES	=	$(addprefix -I, $(HEADERS))

all:  $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) ${OBJS}

$(OBJS) : $(OBJSDIR)

$(OBJSDIR)%.o : $(SRCDIR)%.c
	${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)$(ENV_DIR)
	mkdir -p $(OBJSDIR)$(SELFCMD_DIR)

clean:
	$(RM) $(OBJSDIR)

fclean: clean
	${RM} ${NAME}
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug lib
