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

// TEST(lexer, normal)
// {
// 	char *input = ft_strdup("\"'=");

// 	std::vector<std::pair<t_tokentype, std::string>> expected = {
// 		{TOKEN_DQUOTE, "\""},
// 		{TOKEN_SQUOTE, "'"},
// 		{TOKEN_ASSIGN, "="},
// 		{TOKEN_EOF, ""},
// 	};

// 	t_lexer *lexer = new_lexer(input);
// 	for (auto &expected_token : expected)
// 	{
// 		t_token *token = next_token(lexer);
// 		compare_token(token, expected_token);
// 		delete_token(token);
// 	}
// 	delete_lexer(lexer);
// }

TEST(lexer, single_term)
{
	char *input = ft_strdup("><|$");

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_PIPE, "|"},
		{TOKEN_ENV, "$"},
		{TOKEN_EOF, ""},
	};

	t_lexer *lexer = new_lexer(input);
	for (auto &expected_token : expected)
	{
		t_token *token = next_token(lexer);
		compare_token(token, expected_token);
		delete_token(token);
	}
	delete_lexer(lexer);
}

TEST(lexer, word)
{
	char *input = ft_strdup("echo hello");

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hello"},
		{TOKEN_EOF, ""},
	};

	t_lexer *lexer = new_lexer(input);
	for (auto &expected_token : expected)
	{
		t_token *token = next_token(lexer);
		compare_token(token, expected_token);
		delete_token(token); }
	delete_lexer(lexer);
}

TEST(lexer, heredoc_append)
{
	char *input = ft_strdup("<< >> < >");

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_HEREDOC, "<<"},
		{TOKEN_REDIRECT_APPEND, ">>"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_EOF, ""},
	};

	t_lexer *lexer = new_lexer(input);
	for (auto &expected_token : expected)
	{
		t_token *token = next_token(lexer);
		compare_token(token, expected_token);
		delete_token(token);
	}
	delete_lexer(lexer);
}

TEST(lexer, env)
{
	char *input = ft_strdup("$PATH $?");
	// "echo "hoge \n fuga""

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_ENV, "$PATH"},
		{TOKEN_EXIT_STATUS, "$?"},
		{TOKEN_EOF, ""},
	};

	t_lexer *lexer = new_lexer(input);
	for (auto &expected_token : expected)
	{
		t_token *token = next_token(lexer);
		compare_token(token, expected_token);
		delete_token(token);
	}
	delete_lexer(lexer);
}

TEST(lexer, quote)
{
	char *input = ft_strdup("echo 'hello' \"hello\" joined'hello' joined\"hello\"");

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "'hello'"},
		{TOKEN_IDENT, "\"hello\""},
		{TOKEN_IDENT, "joined'hello'"},
    {TOKEN_IDENT, "joined\"hello\""},
		{TOKEN_EOF, ""},
	};

	t_lexer *lexer = new_lexer(input);
	for (auto &expected_token : expected)
	{
		t_token *token = next_token(lexer);
		compare_token(token, expected_token);
		delete_token(token);
	}
	delete_lexer(lexer);
}
