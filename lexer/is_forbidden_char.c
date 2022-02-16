#include "libft.h"
#include "lexer.h"
#include <stdbool.h>

bool	is_forbidden_char(char c)
{
	const char *forbidden_chars = "*?[#~%&;()`\\";
	return (ft_strchr(forbidden_chars, c) != NULL);
}
