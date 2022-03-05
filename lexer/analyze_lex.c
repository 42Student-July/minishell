#include "common.h"
#include "lexer.h"
#include <unistd.h>
#include <readline/history.h>

static t_lexer_product	*new_lexer_product(void)
{
	t_lexer_product	*product;

	product = ft_calloc(1, sizeof(t_lexer_product));
	if (product == NULL)
		exit(EXIT_FAILURE);
	return (product);
}

t_lexer_product	*analyze_lex(const char *line, t_list *env)
{
	t_lexer			*lexer;
	t_token			*token;
	t_lexer_product	*lexer_product;
	bool			flag;

	lexer_product = new_lexer_product();
	lexer = new_lexer(line);
	while (true)
	{
		token = next_token(lexer);
		ft_lstadd_back(&lexer_product->token_list, ft_lstnew(token));
		if (token->type == TOKEN_EOF)
			break ;
	}
	if (((t_token *)lexer_product->token_list->content)->type == TOKEN_EOF)
	{
		ft_lstclear(&lexer_product->token_list, delete_token);
		free(lexer_product);
		return (NULL);
	}
	if (!is_valid_tokens(lexer_product->token_list))
	{
		write(STDERR, "syntax error\n", 13);
		ft_lstclear(&lexer_product->token_list, delete_token);
		free(lexer_product);
		return (NULL);
	}
	flag = true;
	while (lexer->io_here_delimiters != NULL && flag)
	{
		flag = read_heredoc(lexer, env);
	}
	if (!flag)
	{
		ft_lstclear(&lexer_product->token_list, delete_token);
		free(lexer_product);
		return (NULL);
	}
	if (ft_strlen(lexer->input) > 0) // 空文字列をヒストリーに入れないための対処法
		add_history(lexer->input);
	expand_envvar(lexer_product->token_list, env);
	word_split(lexer_product->token_list);
	ft_lstiter(lexer_product->token_list, &expand_quote);
	lexer_product->heredocs = lexer->heredocs;
	delete_lexer_without_heredocs(lexer);
	return (lexer_product);
}
