# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 14:19:20 by mhirabay          #+#    #+#              #
#    Updated: 2022/03/04 21:28:37 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= libselfcmd.a
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -pedantic -g

HEADERS		=	. \
				../ \
				../libft/ \
				../command/includes \
				../error_handle \
				../environ \

INCLUDES	=	$(addprefix -I, $(HEADERS))

SRCS =  self_pwd.c \
		self_cd.c \
		self_cd_utils.c \
		self_echo.c \
		self_exit.c \
		self_env.c \
		self_export.c \
		self_export_utils.c \
		self_unset.c \
		self_cmd_utils.c \

OBJS = ${SRCS:.c=.o}

DEPS = $(OBJS:.o=.d)

RED			=	'\033[31m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
RESET		=	'\033[0m'


all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) ${OBJS}
	@echo $(YELLOW)"@@@@@ $(NAME) compiling done @@@@@"$(RESET)

%.o: %.c
	@echo $(GREEN)"Creating: $@"$(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean
clean:
	@rm -f $(OBJS)
	@echo $(RED)"REMOVE OBJECT FILES $(OBJS)"$(RESET)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"REMOVE $(NAME)"$(RESET)

re: fclean all
