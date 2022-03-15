#include "lexer.h"

void	delete_lexer_product(t_lexer_product *lexer_product)
{
	ft_lstclear(&lexer_product->token_list, delete_token);
	ft_lstclear(&lexer_product->heredocs, ft_kvsdelete);
	free(lexer_product);
}
