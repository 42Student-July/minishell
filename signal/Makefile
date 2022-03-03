# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 23:29:42 by tkirihar          #+#    #+#              #
#    Updated: 2022/02/17 23:17:45 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			libsignal.a

SRCDIR = 		./src/
SRCNAME = 		sigaction.c \
				set_signal_handler_during_command.c \
				set_signal_handler_during_readline.c \
				set_signal_handler_during_heredoc.c \
				reset_signal_handler.c \

SRCS = 			$(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR = 		./obj/
OBJS = 			$(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
RM =			rm -rf
UNAME =			$(shell uname)

HEADERS =		.. \
				./includes/ \

ifeq ($(UNAME),Darwin)
	HEADERS	+=	$(shell brew --prefix readline)/include
endif

INCLUDES = 		$(addprefix -I, $(HEADERS))

.PHONY: all re clean fclean

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rc $(NAME) $(OBJS)

$(OBJSDIR)%.o:	$(SRCDIR)%.c
				mkdir -p $(OBJSDIR)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re:				fclean all

clean:
				$(RM) $(OBJSDIR)

fclean:			clean
				$(RM) $(NAME)
