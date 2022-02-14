#include "command.h"
#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "repl.h"
#include "sigaction.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>

void	start_repl(void)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*token_list;
	char	*line;
	t_list	*cmd;

	token_list = NULL;
	while (true)
	{
		set_interactive_signal();
		line = readline(">> ");
		set_dfl_signal(); // if文の下に置くべきかも？
		if (line == NULL)
			break ;
		lexer = new_lexer(line);
		free(line);
		while (true)
		{
			token = next_token(lexer);
			ft_lstadd_back(&token_list, ft_lstnew(token));
			if (token->type == TOKEN_EOF)
				break ;
		}
		while (lexer->io_here_delimiters != NULL)
		{
			read_heredoc(lexer);
		}
		if (ft_strlen(lexer->input) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(lexer->input);
		print_tokens(token_list);
		cmd = parse_pipe(token_list);
		print_cmd(cmd);
		// execute_cmd(cmd);
		print_kvs(lexer->heredocs);
		ft_lstclear(&token_list, delete_token);
		delete_lexer(lexer);
	}
	clear_history();
}
