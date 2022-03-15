#include "lexer.h"

char	peek_char(t_lexer *lexer)
{
	return (lexer->input[lexer->position + 1]);
}
