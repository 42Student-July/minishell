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
