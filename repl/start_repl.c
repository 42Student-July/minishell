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

void	print_exit_status(void)
{
	if (g_exit_status == 0)
		printf(F_GREEN "%d " F_RESET, g_exit_status);
	else
		printf(F_RED "%d " F_RESET, g_exit_status);
}

char	*do_readline(void)
{
	char	*line;

	// print_exit_status();
	set_signal_handler_during_readline();
	line = readline(">> ");
	set_signal_handler_during_command();
	return (line);
}

bool	command_process(t_exec_attr *ea)
{
	if (!is_valid_cmds(ea->cmd_lst))
	{
		write(STDERR, "syntax error\n", 13);
		g_exit_status = 2;
		ft_lstclear(&ea->cmd_lst, delete_pipe);
		ea->cmd_lst = NULL;
		return (true);
	}
	execute_cmd(ea);
	return (false);
}

void	start_repl(void)
{
	t_exec_attr		*ea;
	t_lexer_product	*lexer_product;
	char			*line;

	init(&ea);
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
		delete_lexer_product(lexer_product);
		if (command_process(ea))
			continue ;
		ft_lstclear(&ea->cmd_lst, delete_pipe);
		// mem_mgt_check();
	}
	free_exec_attr(ea);
	clear_history();
}
