#include "lexer.h"
#include "libft.h"

void read_char(t_lexer *lexer)
{
	if (lexer->read_position >= ft_strlen(lexer->input))
	{
		lexer->ch = '\0';
	}
	else
	{
		lexer->ch = lexer->input[lexer->read_position];
	}
	lexer->position = lexer->read_position;
	lexer->read_position++;
}
