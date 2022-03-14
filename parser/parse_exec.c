#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

t_list	*filter_null_literal_cmd(t_list *lst)
{
	t_list	*now;
	char	*literal;

	if (lst == NULL)
		return (NULL);
	skip_to_null(&lst, &literal);
	if (lst == NULL)
		return (NULL);
	now = ft_lstnew(ft_strdup(lst->content));
	if (now == NULL)
		return (NULL);
	return (copy_except_null(lst, now, literal));
}

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

bool	loop_until_null(t_list *token_list, t_cmd *cmd)
{
	t_token	*token;

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
			return (false);
		}
		ft_lstadd_back(&cmd->args, ft_lstnew(get_literal(token)));
		token_list = token_list->next;
	}
	return (true);
}

void	parse_exec(t_list *token_list, t_cmd **cmd_p)
{
	t_cmd	*cmd;
	t_list	*tmp;

	if (cmd_p == NULL)
		exit(EXIT_FAILURE);
	cmd = *cmd_p;
	if (token_list == NULL)
	{
		cmd->is_invalid_syntax = true;
		return ;
	}
	if (!loop_until_null(token_list, cmd))
		return ;
	if (ft_lstsize(cmd->args) == 0 && ft_lstsize(cmd->filenames_in) == 0
		&& ft_lstsize(cmd->filenames_out) == 0)
		cmd->is_invalid_syntax = true;
	tmp = filter_null_literal_cmd(cmd->args);
	ft_lstclear(&cmd->args, free);
	cmd->args = tmp;
	if (cmd->args != NULL)
	{
		cmd->cmd = ft_strdup(cmd->args->content);
		if (cmd->cmd == NULL)
			exit(EXIT_FAILURE);
	}
}
