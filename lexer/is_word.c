#include "lexer.h"
#include <stdbool.h>

bool is_word(t_tokentype type)
{
	return (type == TOKEN_IDENT || type == TOKEN_DQUOTE || type == TOKEN_SQUOTE);
}
