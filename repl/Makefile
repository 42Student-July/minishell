NAME 		:= librepl.a
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -g

HEADERS		=	. \
				../ \
				../lexer/ \
				../parser/ \
				../libft/ \
				../gnl/ \
				../command/includes \
				../environ/ \
				../error_handle \
				../self_cmd \
				../signal/includes \

INCLUDES	=	$(addprefix -I, $(HEADERS))

SRCS = start_repl.c\

OBJS = ${SRCS:.c=.o}

DEPS = $(OBJS:.o=.d)

# LIBMEM_MGT			=	libmem_mgt/libmem_mgt.a

RED			=	'\033[31m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
RESET		=	'\033[0m'


all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
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
