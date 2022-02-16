#include "lexer.h"

t_lexer_product	*analyze(char *line)
{
	t_lexer_product	*l_product;
	t_lexer			*lexer;
	t_token			*token;

	l_product = (t_lexer_product *)ft_calloc(sizeof(t_lexer_product), 1);
	if (l_product == NULL)
		exit(EXIT_FAILURE);
	lexer = new_lexer(line);
	free(line);
	while (true)
	{
		token = next_token(lexer);
		ft_lstadd_back(&l_product->token_list, ft_lstnew(token));
		if (token->type == TOKEN_EOF)
			break ;
	}
	while (lexer->io_here_delimiters != NULL)
	{
		read_heredoc(lexer);
	}
	l_product->heredocs = lexer->heredocs;
	l_product->input = ft_strdup(lexer->input);
	delete_lexer(lexer);
	return (l_product);
}
