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

TEST(lexer, single_term)
{
	char input[] = "><|$aaa";

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_PIPE, "|"},
		{TOKEN_IDENT, "$aaa"},
		{TOKEN_EOF, "NULL"},
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
	char input[] = "echo hello";

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "hello"},
		{TOKEN_EOF, "NULL"},
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

TEST(lexer, heredoc_append)
{
	char input[] = "<< >> < >";
	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_HEREDOC, "<<"},
		{TOKEN_REDIRECT_APPEND, ">>"},
		{TOKEN_REDIRECT_IN, "<"},
		{TOKEN_REDIRECT_OUT, ">"},
		{TOKEN_EOF, "NULL"},
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
	char input[] = "$PATH $?";
	// "echo "hoge \n fuga""

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "$PATH"},
		{TOKEN_IDENT, "$?"},
		{TOKEN_EOF, "NULL"},
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
	char input[] = "echo 'hello' \"hello\" joined'hello' "
							"joined\"hello\"";

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "echo"},
		{TOKEN_IDENT, "'hello'"},
		{TOKEN_IDENT, "\"hello\""},
		{TOKEN_IDENT, "joined'hello'"},
		{TOKEN_IDENT, "joined\"hello\""},
		{TOKEN_EOF, "NULL"},
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
