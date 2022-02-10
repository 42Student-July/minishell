#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "command.h"
#include "repl.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void start_repl()
{
	t_lexer *lexer;
	t_token *token;
	t_list *token_list;
	char *line;

	token_list = NULL;
	while (true)
	{
		line = readline(">> ");
		if (line == NULL)
			break;
		lexer = new_lexer(line);
		if (ft_strlen(line) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(line);
		while (true)
		{
			token = next_token(lexer);
			ft_lstadd_back(&token_list, ft_lstnew(token));
			if (token->type == TOKEN_EOF)
				break;
		}
		print_tokens(token_list);
		t_list *cmd = parse_pipe(token_list);
		print_cmd(cmd);
		execute_cmd(cmd);
		ft_lstclear(&token_list, delete_token);
		delete_lexer(lexer);
	}
	clear_history();
}
