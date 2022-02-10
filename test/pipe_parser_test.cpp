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

TEST(parse_pipe, no_pipe)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);
	test_t_pipe_cmd expected = {{{"echo", {"echo"}}, {}, {}}};
	t_list *cmd = parse_pipe(input);
	check_pipe_cmd(cmd, expected);
	ft_lstclear(&cmd, &delete_pipe);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_pipe, simple_pipe)
{
	// cat < in.txt | wc -l
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "cat"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "in.txt"},
		{TOKEN_PIPE, "|"},
		{TOKEN_IDENT, "wc"},
		{TOKEN_IDENT, "-l"},
		{TOKEN_EOF, ""},
	};

	t_list *input = init_input_lists(input_vector);

	test_t_pipe_cmd expected = {{{"cat", {"cat"}}, {{"in.txt", false}}, {}},
								{{"wc", {"wc", "-l"}}, {}, {}}};
	t_list *cmd = parse_pipe(input);
	check_pipe_cmd(cmd, expected);
	ft_lstclear(&cmd, &delete_pipe);
	ft_lstclear(&input, &delete_token);
}

TEST(parse_pipe, multiple_pipes)
{
	// cat < in.txt | wc -l
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "cat"},
		{TOKEN_IDENT, "main.c"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_IDENT, "in.txt"},
		{TOKEN_PIPE, "|"},
		{TOKEN_IDENT, "wc"},
		{TOKEN_IDENT, "-l"},
		{TOKEN_PIPE, "|"},
		{TOKEN_IDENT, "wc"},
		{TOKEN_IDENT, "-l"},
		{TOKEN_EOF, ""},
	};

	t_list *input = init_input_lists(input_vector);

	test_t_pipe_cmd expected = {{{"cat", {"cat", "main.c"}}, {{"in.txt", false}}, {}},
								{{"wc", {"wc", "-l"}}, {}, {}},
								{{"wc", {"wc", "-l"}}, {}, {}}};
	t_list *cmd = (t_list *)parse_pipe(input);
	check_pipe_cmd(cmd, expected);
	ft_lstclear(&cmd, &delete_pipe);
	ft_lstclear(&input, &delete_token);
}
