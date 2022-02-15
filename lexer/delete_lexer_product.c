#include "lexer.h"

void	delete_lexer_product(t_lexer_product **l_product)
{
	ft_lstclear(&(*l_product)->token_list, delete_token);
	ft_lstclear(&(*l_product)->heredocs, ft_kvsdelete);
	free((*l_product)->input);
	(*l_product)->input = NULL;
	free(*l_product);
	*l_product = NULL;
}
