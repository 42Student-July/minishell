#include "lexer.h"
#include "libft.h"

void	delete_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	ft_lstclear(&lexer->heredocs, ft_kvsdelete);
	free(lexer);
	lexer = NULL;
	return ;
}

void delete_lexer_without_heredocs(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	free(lexer);
	lexer = NULL;
	return ;
}
