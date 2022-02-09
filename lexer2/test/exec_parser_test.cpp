#include <algorithm>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
extern "C"
{
#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "test_helper.h"
}

TEST(parse_exec, one_command)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hello"},
		{TOKEN_IDENT, "world!"},
		{TOKEN_IDENT, "yay!"},
		{TOKEN_IDENT, "wow!"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::pair<std::string, std::vector<std::string>> expected = {
		"echo",
		{"echo", "hello", "world!", "yay!", "wow!"},
	};

	t_cmd *cmd = (t_cmd *)parse_exec(input);
	check_exec_cmd((t_exec_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_exec, no_args)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::pair<std::string, std::vector<std::string>> expected = {
		"echo",
		{"echo"},
	};

	t_cmd *cmd = (t_cmd *)parse_exec(input);
	check_exec_cmd((t_exec_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_exec, no_args_and_extra_tokens)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "echo2"},
		{TOKEN_IDENT, "echo3"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::pair<std::string, std::vector<std::string>> expected = {
		"echo",
		{"echo", "echo3"},
	};

	t_cmd *cmd = (t_cmd *)parse_exec(input);
	check_exec_cmd((t_exec_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

