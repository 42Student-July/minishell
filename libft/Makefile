# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 18:26:26 by akito             #+#    #+#              #
#    Updated: 2022/02/23 14:53:26 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
CC := gcc
INCLUDES := -I../includes
CFLAGS := $(INCLUDES) -Wall -Wextra -Werror
SRCS :=	ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_iscap_alpha.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c\
		ft_my_putchar.c\
		ft_my_putstr.c\
		ft_my_putnbr.c\
		ft_my_unsigned_putnbr.c\
		ft_my_putbase.c\
		ft_my_putpointer.c\
		ft_my_atof.c\
		ft_isspace.c\
		ft_isletter.c\
		ft_my_lstpop_front.c\
		ft_kvsnew.c\
		ft_kvsget_value.c\
		ft_kvsget_key.c\
		ft_kvsget.c\
		ft_streq.c\
		ft_kvsdelete.c\
		ft_atol.c \
		ft_kvsreplace_value.c\
		ft_strcut_back.c\

B_SRCS=	ft_lstnew.c \
	 ft_lstadd_front.c \
	 ft_lstsize.c \
	 ft_lstlast.c \
	 ft_lstadd_back.c \
	 ft_lstdelone.c \
	 ft_lstclear.c \
	 ft_lstiter.c \
	 ft_lstmap.c \
	 ft_lstdel.c \

OBJS = ${SRCS:.c=.o}
B_OBJS := ${B_SRCS:.c=.o}

RED			=	'\033[31m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
RESET		=	'\033[0m'

ifdef WITH_BONUS
OBJS += $(B_OBJS)
endif

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) ${OBJS}
	@echo $(YELLOW)"@@@@@ libft.a created @@@@@"$(RESET)

%.o: %.c
	@echo $(GREEN)"Creating: $@"$(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -f $(OBJS) $(B_OBJS)
	@echo $(RED)"REMOVE OBJECT FILES $(OBJS) $(B_OBJS)"$(RESET)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"REMOVE $(NAME)"$(RESET)

.PHONY: re
re: fclean all

.PHONY: test
test: bonus
	$(CC) $(CFLAGS) main.c $(NAME)
	./a.out | cat -e

.PHONY: bonus
bonus:
	make WITH_BONUS=1


