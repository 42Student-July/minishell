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
#include "test_helper.h"
}

TEST(word_split, regardless)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hoge"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hoge"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, normal)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "   echo    hoge   "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hoge"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, doubles)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo' 'hoge"},
		{TOKEN_IDENT, "echo\" \"hoge"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo' 'hoge"},
		{TOKEN_IDENT, "echo\" \"hoge"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, quote)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "\"echo\"   hoge    "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "\"echo\""},
		{TOKEN_IDENT, "hoge"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}


TEST(word_split, quoted_space)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "\"    \"a   hoge    "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "\"    \"a"},
		{TOKEN_IDENT, "hoge"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, operators)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo' <<<'hoge"},
		{TOKEN_IDENT, "echo ||hoge  @@xxx"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo' <<<'hoge"},
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "||hoge"},
		{TOKEN_IDENT, "@@xxx"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, echo)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "\"a\"   test    "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "\"a\""},
		{TOKEN_IDENT, "test"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_default)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "\"a\""},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "\"a\""},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_ambiguous_multi)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "\"a\" b"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_ambiguous_null)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "  "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_only_one)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "  test  "},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "test"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_only_one_quoted)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "'  test  '"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "'  test  '"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_only_one_quoted_multi)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "'  test  'hoge' 'fuga"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "'  test  'hoge' 'fuga"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}

TEST(word_split, redirect_only_multi)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "  test  ' hoge 'fuga"},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	std::vector<std::pair<t_tokentype, std::string>> expected_vector = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_IDENT, "NULL"},
		{TOKEN_EOF, ""},
	};
	word_split(input);
	compare_tokens(input, expected_vector);
	ft_lstclear(&input, &delete_token);
}
