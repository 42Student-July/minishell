#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

t_list *parse_pipe_helper(t_list *token_list, t_list **heredocs);

t_list *parse_pipe(t_list *token_list, t_list **heredocs)
{
	t_list *result;
	// t_list *tmp;

	result = parse_pipe_helper(token_list, heredocs);
	if (result == NULL)
		return (NULL);
	// tmp = result;
	// while (tmp != NULL)
	// {
	// 	if (!is_valid_cmd(tmp->content))
	// 	{
	// 		printf("syntax error\n");
	// 		ft_lstclear(&result, delete_pipe);
	// 		result = NULL;
	// 		break;
	// 	}
	// 	tmp = tmp->next;
	// }
	return (result);
}

t_list *parse_pipe_helper(t_list *token_list, t_list **heredocs)
{
	t_list *left_tokens;
	t_list *right_tokens;
	t_token *token;
	t_list *lst;
	t_cmd *cmd;

	left_tokens = token_list;
	if (((t_token *)left_tokens->content)->type == TOKEN_EOF)
	{
		cmd = cmd_init();
		cmd->is_invalid_syntax = true;
		return (ft_lstnew(cmd));
	}
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF)
			break;
		if (token->type == TOKEN_PIPE)
		{
			right_tokens = token_list->next;
			lst = parse_pipe_helper(right_tokens, heredocs);
			if (((t_token *)right_tokens->content)->type == TOKEN_EOF)
				((t_cmd *)lst->content)->is_invalid_syntax = true;
			ft_lstadd_front(&lst, ft_lstnew(parse_cmd(left_tokens, heredocs)));
			return (lst);
		}
		token_list = token_list->next;
	}
	return (ft_lstnew(parse_cmd(left_tokens, heredocs)));
}
