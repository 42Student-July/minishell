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

void compare_token(t_token *token,
				   std::pair<t_tokentype, std::string> expected_token)
{
	EXPECT_EQ(token->type, expected_token.first);
	if (expected_token.second == "")
	{
		EXPECT_STREQ(token->literal, NULL);
	}
	else
	{
		EXPECT_STREQ(token->literal, expected_token.second.c_str());
	}
}

void compare_tokens(t_list *token_list,
					std::vector<std::pair<t_tokentype, std::string>> expected_tokens)
{
	t_list *current = token_list;

	ASSERT_EQ(ft_lstsize(token_list), expected_tokens.size());
	for (auto &expected_token : expected_tokens)
	{
		t_token *token = (t_token *)current->content;
		compare_token(token, expected_token);
		current = current->next;
	}
}

void compare_string(t_list *str_list, std::vector<std::string> expected_strings)
{
	if (expected_strings.size() == 0)
		EXPECT_EQ(str_list, (void *)NULL);
	else
	{
		ASSERT_EQ(expected_strings.size(), ft_lstsize(str_list));
		for (auto &s : expected_strings)
		{
			EXPECT_STREQ(s.c_str(), (char *)str_list->content);
			str_list = str_list->next;
		}
	}
}

void compare_files(t_list *str_list, test_t_file expected_files)
{
	if (expected_files.size() == 0)
		EXPECT_EQ(str_list, (void *)NULL);
	else
	{
		ASSERT_EQ(expected_files.size(), ft_lstsize(str_list));
		for (auto &s : expected_files)
		{
			EXPECT_STREQ(s.first.c_str(),
						 (char *)((t_file *)str_list->content)->filename);
			EXPECT_EQ(s.second, ((t_file *)str_list->content)->is_double);
			str_list = str_list->next;
		}
	}
}

t_list *init_input_lists(std::vector<std::pair<t_tokentype, std::string>> init_tokens)
{
	t_list *list = NULL;

	for (auto &token : init_tokens)
	{
		t_token *t = new_token(token.first, (char *)token.second.c_str());
		ft_lstadd_back(&list, ft_lstnew(t));
	}

	return (list);
}

/*
typedef struct s_redirect_cmd
{
	int type;
	t_cmd *cmd;
	t_list *filenames_in;
	t_list *filenames_out;
	bool is_double;
} t_redirect_cmd;
*/

void check_exec_cmd(t_cmd *result, test_t_exec_cmd expected)
{
	std::string cmd = std::get<0>(expected);
	std::vector<std::string> args = std::get<1>(expected);
	EXPECT_STREQ(cmd.c_str(), result->cmd);
	compare_string(result->args, args);
}

void check_redirect_cmd(t_cmd *result, test_t_cmd expected)
{
	test_t_file expected_in = std::get<2>(expected);
	test_t_file expected_out = std::get<3>(expected);

	compare_files(result->filenames_in, expected_in);
	compare_files(result->filenames_out, expected_out);
}
// cat A | wc -l | cat
// {}
// test_t_redirect_cmd expected = {{"cat", {"cat"}}, {"main.c"}, {"out.txt"},
// false}; test_t_redirect_cmd expected = {{exec_cmd}, {file_ins}, {file_outs},
// bool}; test_t_redirect_cmd arg1 = {{"cat", {"cat", "A"}}, {}, {}, false};
// test_t_redirect_cmd arg2 = {{"wc", {"wc", "-l"}}, {}, {}, false};
// test_t_redirect_cmd arg1 =
// {{"cat", {"cat"}}, {}, {}, false}; {arg1, arg2, arg3}

void check_pipe_cmd(t_list *result, test_t_pipe_cmd expected)
{
	if (expected.size() == 0)
	{
		EXPECT_EQ(result, (void *)NULL);
		return;
	}
	test_t_cmd expected_redirect_cmd = expected[0];
	if (result == NULL)
		return;
	check_redirect_cmd((t_cmd *)result->content, expected_redirect_cmd);
	expected.erase(expected.begin());
	check_pipe_cmd(result->next, expected);
}
