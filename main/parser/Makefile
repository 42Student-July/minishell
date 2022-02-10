NAME 		:= libparser.a
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -pedantic -g

HEADERS		=	. \
				../ \
				../lexer/ \
				../libft/ \
				../parser/ \
				../gnl/

INCLUDES	=	$(addprefix -I, $(HEADERS))

SRCS = parse_exec.c\
		parse_pipe.c\
		parse_redirect.c\
		print_cmd.c\
		delete_cmd.c\
		new_file.c\
		delete_file.c\


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
