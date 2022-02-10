#include "lexer.h"
#include "libft.h"

void skip_whitespace(t_lexer *lexer)
{
	while(ft_isspace(lexer->ch))
		read_char(lexer);
}
