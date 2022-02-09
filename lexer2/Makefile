NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror


LIBFT_DIR	=	libft
GNL_DIR		=	gnl
LEXER_DIR 	= 	lexer
PARSER_DIR 	= 	parser
REPL_DIR 	= 	repl

HEADERS		=	. $(LIBFT_DIR) $(GNL_DIR) $(LEXER_DIR) $(PARSER_DIR) $(REPL_DIR)

LIBFT		=	$(LIBFT_DIR)/libft.a
GNL			=   $(GNL_DIR)/libgnl.a
LIB_LEXER 	=	$(LEXER_DIR)/liblexer.a
LIB_PARSER 	=	$(PARSER_DIR)/libparser.a
LIB_REPL 	=	$(REPL_DIR)/librepl.a

INCLUDES	=	$(addprefix -I, $(HEADERS))

RM			=	rm -f
RM_DIR		=	rm -rf

SRCS	= ./main.c
OBJS	= $(SRCS:.c=.o)



all: $(NAME)

RED			=	'\033[31m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
RESET		=	'\033[0m'

$(NAME): $(LIBFT) $(GNL) $(LIB_LEXER) $(LIB_PARSER) $(LIB_REPL) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LIB_REPL) $(LIB_PARSER) $(LIB_LEXER) $(GNL) $(LIBFT) $(CFLAGS) $(INCLUDES) -lreadline
	@echo $(YELLOW)"@@@@@ $(NAME) compiling done @@@@@"$(RESET)

$(LIBFT): dummy
	@make -C $(LIBFT_DIR) bonus

$(GNL): dummy
	@make -C $(GNL_DIR)

$(LIB_LEXER): dummy
	@make -C $(LEXER_DIR)

$(LIB_PARSER): dummy
	@make -C $(PARSER_DIR)

$(LIB_REPL): dummy
	@make -C $(REPL_DIR)


.PHONY: dummy
dummy:

%.o: %.c
	@echo $(GREEN)"Creating: $@"$(RESET)
	@$(CC) $(INCLUDES) -c $< -o $@ $(CFLAGS)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(GNL_DIR) clean
	@make -C $(LEXER_DIR) clean
	@make -C $(REPL_DIR) clean
	@$(RM) $(OBJS)
	@echo $(RED)"REMOVE OBJECT FILES $(OBJS)"$(RESET)

fclean:	clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean
	@make -C $(LEXER_DIR) fclean
	@make -C $(REPL_DIR) fclean
	@$(RM) $(NAME)
	@echo $(RED)"REMOVE $(NAME)"$(RESET)
	@$(RM) ./tester
	@echo $(RED)"REMOVE tester"$(RESET)

re:	fclean all

GTEST_DIR	=	./test
GTEST	=	$(GTEST_DIR)/gtest $(GTEST_DIR)/googletest-release-1.11.0

$(GTEST):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	rm -rf release-1.11.0.tar.gz
	python googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTEST_DIR)
	mv googletest-release-1.11.0 $(GTEST_DIR)


#it is important to compile the library with right order (libft is the latest)
SRCS_TEST = test/test_helper.cpp\
			test/lexer_test.cpp\
			test/exec_parser_test.cpp\
			test/redirect_parser_test.cpp\
			test/pipe_parser_test.cpp\

.PHONY: test
test: test-build
	./tester

test-build: $(LIBFT) $(LIB_LEXER) $(LIB_PARSER) $(GTEST) $(SRCS_TEST)
	g++ -std=c++11  $(SRCS_TEST) $(LIB_PARSER) $(LIB_LEXER) $(LIBFT)  $(GTEST_DIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(GTEST_DIR)/gtest/gtest-all.cc \
	 -DDEBUG \
	-I$(GTEST_DIR) -I/usr/local/opt/llvm/include $(INCLUDES) -I test -lpthread -o tester -lgtest -g

.PHONY: all clean fclean re bonus
