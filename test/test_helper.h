#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <string>
#include <vector>

typedef std::vector<std::string> VS;

typedef std::vector<std::pair<std::string, bool>> test_t_file;
typedef std::tuple<std::string, VS> test_t_exec_cmd;
typedef std::tuple<std::string, VS, test_t_file, test_t_file> test_t_cmd;

typedef std::vector<test_t_cmd> test_t_pipe_cmd;
void compare_token(t_token *token,
				   std::pair<t_tokentype, std::string> expected_token);

void compare_string(t_list *str_list, std::vector<std::string> expected_strings);
t_list *init_input_lists(std::vector<std::pair<t_tokentype, std::string>> init_tokens);
void check_exec_cmd(t_cmd *result, test_t_exec_cmd expected);
void check_redirect_cmd(t_cmd *result, test_t_cmd expected);
void check_pipe_cmd(t_list *result, test_t_pipe_cmd expected);
void compare_files(t_list *str_list, test_t_file expected_files);
#endif
