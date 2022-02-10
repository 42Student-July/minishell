#include "lexer.h"
#include "libft.h"

void	delete_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	free(lexer);
	lexer = NULL;
	return ;
}
