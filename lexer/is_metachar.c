#include "lexer.h"
#include <stdbool.h>

bool	is_metachar(const char c)
{
	const char	meta_chars[] = "|<>";

	return ((ft_strchr(meta_chars, c) != NULL) || ft_isspace(c));
}
