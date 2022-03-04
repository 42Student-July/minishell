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

// プロンプトに終了ステータスが表示されるようになる関数
// おそらくテスターが通らなくなるのでデバッグ用
void	print_exit_status()
{
	if (g_exit_status == 0)
		printf(F_GREEN"%d "F_RESET, g_exit_status);
	else
		printf(F_RED"%d "F_RESET, g_exit_status);
}

char	*do_readline()
{
	char	*line;

	// print_exit_status(); //テスターに通すときはコメントアウト
	set_signal_handler_during_readline();
	line = readline(">> ");
	set_signal_handler_during_command();
	return (line);
}

void	start_repl(void)
{
	t_lexer *lexer;
	t_token *token;
	t_list *token_list;
	t_exec_attr *ea;
	char *line;
	bool flag;

	token_list = NULL;
	init_new(&ea);
	while (true)
	{
		line = do_readline();
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
		if (((t_token *)token_list->content)->type == TOKEN_EOF)
		{
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		if (!is_valid_tokens(token_list))
		{
			write(STDERR, "syntax error\n", 13);
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		flag = true;
		while (lexer->io_here_delimiters != NULL && flag)
		{
			flag = read_heredoc(lexer, ea->env_lst);
		}
		if (!flag)
		{
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		if (ft_strlen(lexer->input) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(lexer->input);
		expand_envvar(token_list, ea->env_lst);
		word_split(token_list);
		ft_lstiter(token_list, &expand_quote);
		ea->cmd_lst = parse_pipe(token_list, &lexer->heredocs);
		if (!is_valid_cmds(ea->cmd_lst))
		{
			write(STDERR, "syntax error\n", 13);
			g_exit_status = 2;
			ft_lstclear(&token_list, delete_token);
			token_list = NULL;
			ft_lstclear(&ea->cmd_lst, delete_pipe);
			ea->cmd_lst = NULL;
			continue;
		}
		execute_cmd(ea);
		ft_lstclear(&token_list, delete_token);
		delete_lexer(lexer);
	}
	clear_history();
}
