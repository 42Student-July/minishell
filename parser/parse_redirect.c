#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>

/*
input: cat fuga.txt ... hoge.txt > b.txt
[TOKEN_IDENT, TOKEN_IDENT, TOKEN_REDIRECT_OUT, TOKEN_IDENT, TOKEN_EOF]
*/

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	return (cmd);
}

t_cmd	*parse_cmd(t_list *token_list, t_list **heredocs)
{
	t_cmd	*cmd;
	t_token	*token;
	char	*filename;

	cmd = cmd_init();
	parse_exec(token_list, &cmd);
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_REDIRECT_IN)
		{
			token = token_list->next->content;
			ft_lstadd_back(&cmd->filenames_in,
							ft_lstnew(new_file(token->literal, false)));
		}
		else if (token->type == TOKEN_REDIRECT_OUT)
		{
			token = token_list->next->content;
			ft_lstadd_back(&cmd->filenames_out,
							ft_lstnew(new_file(token->literal, false)));
		}
		else if (token->type == TOKEN_REDIRECT_APPEND)
		{
			token = token_list->next->content;
			ft_lstadd_back(&cmd->filenames_out,
							ft_lstnew(new_file(token->literal, true)));
		}
		else if (token->type == TOKEN_HEREDOC)
		{
			token = token_list->next->content;
			filename = ft_kvsget(*heredocs, token->literal);
			printf("%s\n", filename);
			ft_lstadd_back(&cmd->filenames_in, ft_lstnew(new_file(filename,
							true)));
		}
		token_list = token_list->next;
	}
	return (cmd);
}
