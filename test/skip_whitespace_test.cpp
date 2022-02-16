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

// TEST(trim_whitespace, word)
// {
// 	char *input = ft_strdup("echo hello");

// 	std::vector<std::pair<t_tokentype, std::string>> expected = {
// 		{TOKEN_IDENT, "echo"},
// 		{TOKEN_WHITESPACE, " "},
// 		{TOKEN_IDENT, "hello"},
// 		{TOKEN_EOF, ""},
// 	};

// 	t_lexer_product *lexer_product = analyze(input);

// }
