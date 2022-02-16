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
	t_lexer_product *l_product;
	t_exec_attr *ea;
	char *line;

	init_new(&ea);
	while (true)
	{
		set_interactive_signal();
		line = readline(">> ");
		set_dfl_signal(); // if文の下に置くべきかも？
		if (line == NULL)
			break ;
		l_product = analyze(line);
		if (ft_strlen(l_product->input) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(l_product->input);
		// envvar_expansion(l_product);
		split_whitespace(l_product);
		print_tokens(l_product->token_list);
		ea->cmd_lst = parse_pipe(l_product->token_list, &l_product->heredocs);
		print_cmds(ea->cmd_lst);
		// execute_cmd(ea);
		print_kvs(l_product->heredocs);
		delete_lexer_product(&l_product);
	}
	clear_history();
}
