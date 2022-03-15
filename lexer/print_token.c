#include "lexer.h"
#include "libft.h"
#include "common.h"

char	*get_token_type_name(t_tokentype type)
{
	if (type == TOKEN_ILLEGAL)
		return ("ILLEGAL");
	else if (type == TOKEN_EOF)
		return ("EOF");
	else if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_IDENT)
		return ("IDENT");
	else if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	else
		return ("UNKNOWN");
}

void	print_token(t_token *token)
{
	ft_putstr_fd("type: [", STDOUT);
	ft_putstr_fd(get_token_type_name(token->type), STDOUT);
	ft_putstr_fd("], ", STDOUT);
	ft_putstr_fd("\tliteral: [", STDOUT);
	if (token->literal != NULL)
		ft_putstr_fd(token->literal, STDOUT);
	else
		ft_putstr_fd("NULL", STDOUT);
	ft_putstr_fd("]\n", STDOUT);
	return ;
}

void	print_tokens(t_list *token_list)
{
	t_list	*list_node;

	list_node = token_list;
	while (list_node != NULL)
	{
		print_token(list_node->content);
		list_node = list_node->next;
	}
	return ;
}
