#include "lexer.h"
#include <stdbool.h>

bool	is_word_token(t_tokentype type)
{
	return (type == TOKEN_IDENT);
}
