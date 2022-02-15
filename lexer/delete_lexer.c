#include "lexer.h"
#include "libft.h"

void	delete_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	free(lexer);
	ft_lstclear(&lexer->io_here_delimiters, free);
	ft_lstclear(&lexer->heredocs, ft_kvsdelete);
	lexer = NULL;
	return ;
}
