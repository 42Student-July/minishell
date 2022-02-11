#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>

/*
input: cat fuga.txt ... hoge.txt > b.txt
[TOKEN_IDENT, TOKEN_IDENT, TOKEN_REDIRECT_OUT, TOKEN_IDENT, TOKEN_EOF]
*/

t_redirect_cmd *redirect_cmd_init()
{
	t_redirect_cmd *cmd;

	cmd = (t_redirect_cmd *)ft_calloc(sizeof(t_redirect_cmd), 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	cmd->type = CMD_REDIRECT;
	return (cmd);
}

t_cmd *parse_redirect(t_list *token_list)
{
	t_redirect_cmd *redirect_cmd;
	t_token *token;

	redirect_cmd = redirect_cmd_init();
	redirect_cmd->cmd = (t_exec_cmd *)parse_exec(token_list);
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break;
		if (token->type == TOKEN_REDIRECT_IN)
		{
			token = token_list->next->content;
			ft_lstadd_back(&redirect_cmd->filenames_in,
						   ft_lstnew(new_file(token, false)));
		}
		else if (token->type == TOKEN_REDIRECT_OUT)
		{
			token = token_list->next->content;
			ft_lstadd_back(&redirect_cmd->filenames_out,
						   ft_lstnew(new_file(token, false)));
		}
		else if (token->type == TOKEN_REDIRECT_APPEND)
		{
			token = token_list->next->content;
			ft_lstadd_back(&redirect_cmd->filenames_out,
						   ft_lstnew(new_file(token, true)));
		}
		token_list = token_list->next;
	}

	return ((t_cmd *)redirect_cmd);
}
