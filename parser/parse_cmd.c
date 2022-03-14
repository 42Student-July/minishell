#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>

/*
input: cat fuga.txt ... hoge.txt > b.txt
[TOKEN_IDENT, TOKEN_IDENT, TOKEN_REDIRECT_OUT, TOKEN_IDENT, TOKEN_EOF]
*/

t_cmd	*parse_cmd(t_list *token_list, t_list **heredocs)
{
	t_cmd	*cmd;
	t_token	*token;
	t_list	*lst;
	char	*filename;

	cmd = cmd_init();
	lst = token_list;
	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_REDIRECT_IN)
		{
			token = lst->next->content;
			ft_lstadd_back(&cmd->filenames_in,
				ft_lstnew(new_file(token->literal, false)));
		}
		else if (token->type == TOKEN_REDIRECT_OUT)
		{
			token = lst->next->content;
			ft_lstadd_back(&cmd->filenames_out,
				ft_lstnew(new_file(token->literal, false)));
		}
		else if (token->type == TOKEN_REDIRECT_APPEND)
		{
			token = lst->next->content;
			ft_lstadd_back(&cmd->filenames_out,
				ft_lstnew(new_file(token->literal, true)));
		}
		else if (token->type == TOKEN_HEREDOC)
		{
			token = lst->next->content;
			filename = ft_kvsget(*heredocs, token->literal);
			ft_lstadd_back(&cmd->filenames_in,
				ft_lstnew(new_file(filename, true)));
		}
		lst = lst->next;
	}
	parse_exec(token_list, &cmd);
	return (cmd);
}
