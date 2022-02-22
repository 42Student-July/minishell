#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

void	skip_redirect(t_list **token_list, t_cmd *cmd)
{
	t_token	*token;

	if (token_list == NULL || *token_list == NULL)
		exit(EXIT_FAILURE);
	*token_list = (*token_list)->next;
	if (*token_list == NULL)
	{
		cmd->is_invalid_syntax = true;
		return ;
	}
	token = (t_token *)(*token_list)->content;
	if (!is_word_token(token->type))
	{
		cmd->is_invalid_syntax = true;
		return ;
	}
	*token_list = (*token_list)->next;
}

void	parse_exec(t_list *token_list, t_cmd **cmd_p)
{
	t_token	*token;
	t_cmd	*cmd;

	if (cmd_p == NULL)
		exit(EXIT_FAILURE);
	cmd = *cmd_p;
	if (token_list == NULL)
	{
		cmd->is_invalid_syntax = true;
		return ;
	}
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break ;
		if (is_redirect(token->type))
		{
			skip_redirect(&token_list, cmd);
			continue ;
		}
		if (!is_word_token(token->type))
		{
			cmd->is_invalid_syntax = true;
			return ;
		}
		ft_lstadd_back(&cmd->args, ft_lstnew(get_literal(token)));
		token_list = token_list->next;
	}
	if (cmd->args != NULL)
	{
		cmd->cmd = ft_strdup(cmd->args->content);
		if (cmd->cmd == NULL)
			exit(EXIT_FAILURE);
	}
}
