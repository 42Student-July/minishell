# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 23:29:42 by tkirihar          #+#    #+#              #
#    Updated: 2022/02/13 00:29:23 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			libsignal.a

SRCDIR = 		./src/
SRCNAME = 		sigaction.c \
				set_signal.c \

SRCS = 			$(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR = 		./obj/
OBJS = 			$(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
RM =			rm -rf

HEADERS = 		./includes/ \
				$(shell brew --prefix readline)/include \

INCLUDES = 		$(addprefix -I, $(HEADERS))

RLFLAGS = 		-lreadline -lhistory -L$(shell brew --prefix readline)/lib

.PHONY: all re clean fclean

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rc $(NAME) $(OBJS)

$(OBJSDIR)%.o:	$(SRCDIR)%.c
				mkdir -p $(OBJSDIR)
				$(CC) $(INCLUDES) $(RLFLAGS) -c $< -o $@

re:				fclean all

clean:
				$(RM) $(OBJSDIR)

fclean:			clean
				$(RM) $(NAME)