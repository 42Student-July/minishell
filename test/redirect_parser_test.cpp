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

TEST(parse_redirect, simple_redirect_in)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "cat"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "test.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);
	test_t_redirect_cmd expected = {
		{"cat", {"cat"}},
		{{"test.txt", false}},
		{},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, simple_redirect_out)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "test.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"echo", {"echo"}},
		{},
		{{"test.txt", false}},
	};
	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, simple_redirect_append)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_APPEND, ">>"},
		{TOKEN_IDENT, "test.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"echo", {"echo"}},
		{},
		{{"test.txt", true}},
	};
	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, redirect_out_triple)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "test1.txt"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "test2.txt"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "test3.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"echo", {"echo"}},
		{},
		{{"test1.txt", false}, {"test2.txt", false}, {"test3.txt", false}},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, redirect_in_triple)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "test1.txt"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "test2.txt"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "test3.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"echo", {"echo"}},
		{{"test1.txt", false}, {"test2.txt", false}, {"test3.txt", false}},
		{},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, redirect_multiple)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "cat"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "out1.txt"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "README.md"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "out2.txt"},
		{TOKEN_REDIRECT_APPEND, ">>"},
		{TOKEN_IDENT, "append1.txt"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "out3.txt"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"cat", {"cat"}},
		{{"main.c", false}, {"README.md", false}},
		{{"out1.txt", false},
		 {"out2.txt", false},
		 {"append1.txt", true},
		 {"out3.txt", false}},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, redirect_multiple2)
{
	// cat < main.c README.md > out1.txt main.c
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "cat"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_IDENT, "README.md"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "out.txt"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);
	test_t_redirect_cmd expected = {
		{"cat", {"cat", "README.md", "main.c"}},
		{{"main.c", false}},
		{{"out.txt", false}},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, redirect_before_command)
{
	// < main.c > out1.txt cat
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "out.txt"},
		{TOKEN_IDENT, "cat"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {
		{"cat", {"cat"}},
		{{"main.c", false}},
		{{"out.txt", false}},
	};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_redirect, only_input)
{
	// < main.c > out1.txt cat
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	test_t_redirect_cmd expected = {{}, {{"main.c", false}}, {}};

	t_cmd *cmd = (t_cmd *)parse_redirect(input);
	check_redirect_cmd((t_redirect_cmd *)cmd, expected);
	delete_cmd(&cmd);
	ft_lstclear(&input, &delete_token);
}

// EXIT_FAILURE
//
// TEST(parse_redirect, syntax_error)
// {
// 	// < main.c > out1.txt cat
// 	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
// 		{TOKEN_REDIRECT_IN, "<"},
// 		{TOKEN_IDENT, "main.c"},
// 		{TOKEN_REDIRECT_OUT, ">"},
// 		{TOKEN_REDIRECT_OUT, ">"},
// 		{TOKEN_EOF, ""},
// 	};
// 	t_list *input = init_input_lists(input_vector);

// 	t_cmd *cmd = (t_cmd *)parse_redirect(input);
// 	// exit failure
// }
