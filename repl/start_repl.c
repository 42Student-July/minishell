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
// char	*do_readline()
// {
// 	char	*line;
// 	char	*prompt;

// 	prompt = ft_strjoin(ft_itoa(g_exit_status), " >> ");
// 	if (prompt == NULL)
// 		exit(EXIT_FAILURE);
// 	set_interactive_signal();
// 	line = readline(prompt);
// 	set_dfl_signal();
// 	free(prompt);
// 	return (line);
// }

char	*do_readline()
{
	char	*line;

	set_interactive_signal();
	line = readline(">> ");
	set_dfl_signal();
	return (line);
}

void	start_repl(void)
{
	t_lexer *lexer;
	t_token *token;
	t_list *token_list;
	t_exec_attr *ea;
	char *line;

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
		print_tokens(token_list);
		if (((t_token *)token_list->content)->type == TOKEN_EOF)
		{
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		if (!is_valid_tokens(token_list))
		{
			printf("syntax error\n");
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		while (lexer->io_here_delimiters != NULL)
		{
			read_heredoc(lexer, ea->env_lst);
		}
		if (ft_strlen(lexer->input) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(lexer->input);
		// print_tokens(token_list);
		// print_tokens(token_list);
		// print_kvs(lexer->heredocs);
		// print_kvs(ea->env_lst);
		expand_envvar(token_list, ea->env_lst);
		// print_tokens(token_list);
		// word_split(token_list);
		ft_lstiter(token_list, &expand_quote);
		// print_tokens(token_list);
		ea->cmd_lst = parse_pipe(token_list, &lexer->heredocs);
		print_cmds(ea->cmd_lst);
		if (!is_valid_cmds(ea->cmd_lst))
		{
			printf("syntax error\n");
			ft_lstclear(&token_list, delete_token);
			continue;
		}
		execute_cmd(ea);
		ft_lstclear(&token_list, delete_token);
		delete_lexer(lexer);
	}
	clear_history();
}
