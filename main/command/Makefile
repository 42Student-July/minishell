# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/09 18:00:51 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= command.a

ENV_DIR := environ/
ENV_SRCNAME := 	env_lst.c \
				export_lst.c \
				kvs_utils.c \
				lst_utils.c \

ENV_SRCS = $(addprefix $(ENV_DIR), $(ENV_SRCNAME))

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
SRCNAME	:=	main_test.c \
			execute_builtin.c \
			execute_self.c \
			error_handling.c \
			redirect_process.c \
			debug.c \
			init.c \
			create_cmd.c \
			$(ENV_SRCS) \
			$(SELFCMD_SRCS) \

SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
INC		:= -I ./includes/
RM		:= rm -rf
LDFLAGS := -Llib/ft_printf -Llib/gnl -Llib/libft -Llib/ft_lst
LIBS 	:= -lftprintf -lgnl -lft -llst

all: lib $(NAME)

lib :
	make -C lib/ft_printf
	make -C lib/gnl
	make -C lib/libft
	make -C lib/ft_lst

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) ${LDFLAGS} ${LIBS} $^ -o $@

$(OBJS) : $(OBJSDIR)

$(OBJSDIR)%.o : $(SRCDIR)%.c
	${CC} ${CFLAGS} $(INC) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)$(ENV_DIR)
	mkdir -p $(OBJSDIR)$(SELFCMD_DIR)

clean:
	make clean -C lib/ft_printf
	make clean -C lib/libft
	make clean -C lib/ft_lst
	$(RM) $(OBJSDIR)

fclean: clean
	make fclean -C lib/ft_printf
	make fclean -C lib/libft
	make fclean -C lib/ft_lst
	${RM} ${NAME}
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug lib
