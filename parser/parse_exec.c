#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

t_cmd *exec_cmd_init()
{
	t_exec_cmd *cmd;

	cmd = (t_exec_cmd *)ft_calloc(sizeof(t_exec_cmd), 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	cmd->type = CMD_EXEC;
	return ((t_cmd *)cmd);
}

void skip_redirect(t_list **token_list)
{
	t_token *token;

	if (token_list == NULL || *token_list == NULL)
		exit(EXIT_FAILURE);
	*token_list = (*token_list)->next;
	if (*token_list == NULL)
		exit(EXIT_FAILURE);
	token = (t_token *)(*token_list)->content;
	if (token->type != TOKEN_IDENT)
		exit(EXIT_FAILURE);
	*token_list = (*token_list)->next;
}

// echo "hello" > hoge.txt
t_cmd *parse_exec(t_list *token_list)
{
	t_exec_cmd *exec_cmd;
	t_token *token;

	if (token_list == NULL)
		return (NULL);

	exec_cmd = (t_exec_cmd *)exec_cmd_init();
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break;
		if (is_redirect(token->type))
		{
			skip_redirect(&token_list);
			continue;
		}
		if (token->type != TOKEN_IDENT)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&exec_cmd->args, ft_lstnew(get_literal(token)));
		token_list = token_list->next;
	}
	if (exec_cmd->args != NULL)
	{
		exec_cmd->cmd = ft_strdup(exec_cmd->args->content);
		if (exec_cmd->cmd == NULL)
			exit(EXIT_FAILURE);
	}
	return ((t_cmd *)exec_cmd);
}
