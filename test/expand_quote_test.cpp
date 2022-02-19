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

TEST(expand_quote, dquote)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "hoge\"quote\""},
		{TOKEN_IDENT, "\"hoge\"quote"},
		{TOKEN_IDENT, "\"hoge\"\"quote\""},
		{TOKEN_IDENT, "\"ho\"ge\"\"qu\"ote\""},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);


	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_EOF, ""},
	};
	ft_lstiter(input, &expand_quote);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(expand_quote, squote)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "hoge'quote'"},
		{TOKEN_IDENT, "'hoge'quote"},
		{TOKEN_IDENT, "'hoge''quote'"},
		{TOKEN_IDENT, "'ho'ge''qu'ote'"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);


	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_EOF, ""},
	};
	ft_lstiter(input, &expand_quote);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(expand_quote, combine)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "\"hoge\"'quote'"},
		{TOKEN_IDENT, "\"'hoge'quote\""},
		{TOKEN_IDENT, "'hoge\"quote\"'"},
		{TOKEN_IDENT, "\"ho'g'e'\"'  'quote"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);


	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "hogequote"},
		{TOKEN_IDENT, "'hoge'quote"},
		{TOKEN_IDENT, "hoge\"quote\""},
		{TOKEN_IDENT, "ho'g'e'  quote"},
		{TOKEN_EOF, ""},
	};
	ft_lstiter(input, &expand_quote);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

