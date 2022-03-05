#include "command.h"
#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "repl.h"
#include "sigaction.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdio.h>

// プロンプトに終了ステータスが表示されるようになる関数
// おそらくテスターが通らなくなるのでデバッグ用
void	print_exit_status(void)
{
	if (g_exit_status == 0)
		printf(F_GREEN "%d " F_RESET, g_exit_status);
	else
		printf(F_RED "%d " F_RESET, g_exit_status);
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
	t_exec_attr		*ea;
	t_lexer_product	*lexer_product;
	char			*line;

	init_new(&ea);
	while (true)
	{
		line = do_readline();
		if (line == NULL)
			break ;
		lexer_product = analyze_lex(line, ea->env_lst);
		free(line);
		if (lexer_product == NULL)
			continue ;
		ea->cmd_lst = parse_pipe(lexer_product->token_list,
				&lexer_product->heredocs);
		if (!is_valid_cmds(ea->cmd_lst))
		{
			write(STDERR, "syntax error\n", 13);
			g_exit_status = 2;
			ft_lstclear(&lexer_product->token_list, delete_token);
			lexer_product->token_list = NULL;
			free(lexer_product);
			ft_lstclear(&ea->cmd_lst, delete_pipe);
			ea->cmd_lst = NULL;
			continue ;
		}
		execute_cmd(ea);
		ft_lstclear(&lexer_product->token_list, delete_token);
		free_lst(ea->cmd_lst);
	}
	clear_history();
}
