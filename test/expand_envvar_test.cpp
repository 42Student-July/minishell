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

int g_exit_status = 0;

TEST(env, replace_string)
{
	char *input = ft_strdup("$HOME");
	char *key = ft_strdup("HOME");
	char *value = ft_strdup("/home/user");
	char *expected = ft_strdup("/home/user");
	char *result = replace_string(&input[1], key, value);
	EXPECT_STREQ(result, expected);
	free(input);
	free(key);
	free(value);
	free(expected);
	free(result);
}

TEST(env, expand_single_envvar)
{
	char *input = ft_strdup("$HOME");
	char *key = ft_strdup("HOME");
	char *value = ft_strdup("/home/user");
	char *expected = ft_strdup("/home/user");
	size_t i = 0;
	char *result = expand_single_envvar(input, key, value, &i);
	EXPECT_STREQ(result, expected);
	free(input);
	free(key);
	free(value);
	free(expected);
	free(result);
}

TEST(env, expand_envvar_str)
{
	char *input = ft_strdup("hoge$HOME");
	char *key = ft_strdup("HOME");
	char *value = ft_strdup("/home/user");
	char *expected = ft_strdup("hoge/home/user");
	t_list *lst = ft_lstnew(ft_kvsnew(key, value));
	char *result = expand_envvar_str(input, lst);
	EXPECT_STREQ(result, expected);
	free(input);
	free(key);
	free(value);
	free(expected);
	free(result);
	ft_lstclear(&lst, &ft_kvsdelete);
}

TEST(env, expand_envvar_multi)
{
	char *input = ft_strdup("hoge\"$KEY\"$KEYa@$KEY$KEY");
	char *key = ft_strdup("KEY");
	char *value = ft_strdup("|replaced|");
	char *expected = ft_strdup("hoge\"|replaced|\"@|replaced||replaced|");
	t_list *lst = ft_lstnew(ft_kvsnew(key, value));
	char *result = expand_envvar_str(input, lst);
	EXPECT_STREQ(result, expected);
	free(input);
	free(key);
	free(value);
	free(expected);
	free(result);
	ft_lstclear(&lst, &ft_kvsdelete);
}

TEST(env, expand_envvar_tail)
{
	char *input = ft_strdup("hoge$KEY$");
	char *key = ft_strdup("KEY");
	char *value = ft_strdup("|replaced|");
	char *expected = ft_strdup("hoge|replaced|$");
	t_list *lst = ft_lstnew(ft_kvsnew(key, value));
	char *result = expand_envvar_str(input, lst);
	EXPECT_STREQ(result, expected);
	free(input);
	free(key);
	free(value);
	free(expected);
	free(result);
	ft_lstclear(&lst, &ft_kvsdelete);
}


TEST(env, expand_envvar_wtf3)
{
	std::vector<std::pair<t_tokentype, std::string>> input_vector = {
		{TOKEN_IDENT, "hoge\"'$A'\""},
		{TOKEN_IDENT, "hoge\"$A\""},
		{TOKEN_IDENT, "fuga'\"$A\"'"},
		{TOKEN_IDENT, "hoge'$A'"},
		{TOKEN_IDENT, "hoge\"'$A'\""},
		{TOKEN_EOF, ""},
	};
	t_list *input = init_input_lists(input_vector);

	char *key = ft_strdup("A");
	char *value = ft_strdup("|wtf|");
	t_list *lst = ft_lstnew(ft_kvsnew(key, value));

	std::vector<std::pair<t_tokentype, std::string>> expected = {
		{TOKEN_IDENT, "hoge\"'|wtf|'\""},
		{TOKEN_IDENT, "hoge\"|wtf|\""},
		{TOKEN_IDENT, "fuga'\"$A\"'"},
		{TOKEN_IDENT, "hoge'$A'"},
		{TOKEN_IDENT, "hoge\"'|wtf|'\""},
		{TOKEN_EOF, ""},
	};
	expand_envvar(input, lst);
	compare_tokens(input, expected);
	free(input);
	free(key);
	free(value);
	ft_lstclear(&lst, &ft_kvsdelete);
}

TEST(env, expand_envvar_exit_status)
{
	g_exit_status = 65536;
	char *input = ft_strdup("fuga$?hoge");
	char *expected = ft_strdup("fuga65536hoge");
	char *result = expand_envvar_str(input, NULL);
	EXPECT_STREQ(result, expected);
	free(input);
	free(expected);
	free(result);
}