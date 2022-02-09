#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_HISTORY_NO 10

/*
	実行前に環境変数PS2にプロンプト用の文字列を設定する
	例：export PS2='minishell $'
	コンパイルにはオプションとして-lreadlineを入れる
	実行中は上矢印キーで過去のコマンドが入力候補として表示される
	ctrl+d で終了
	MAX_HISTORY_NO より多くコマンドを入力すると古いコマンドから履歴が削除される
*/
int	main(void)
{
	char *prompt = "minishell $";
	char *line = NULL;
	int history_i = 0;
	HIST_ENTRY *rm_history;

	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		add_history(line);
		if (++history_i > MAX_HISTORY_NO)
		{
			rm_history = remove_history(0);
			free(rm_history);
		}
		free(line);
	}
	printf("\n");
	clear_history();
	return (EXIT_SUCCESS);
}