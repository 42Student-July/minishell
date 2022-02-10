#include "lexer.h"
#include "libft.h"

t_lexer	*new_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
		exit(EXIT_FAILURE);
	lexer->input = input;
	lexer->position = 0;
	lexer->read_position = 0;
	lexer->ch = '\0';
	read_char(lexer);
	return (lexer);
}