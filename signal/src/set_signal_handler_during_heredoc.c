#include  "sigaction.h"
#include <unistd.h>

void handle_sigint_during_heredoc(int sig)
{
	(void)sig;
	// printf("\n");
	// print_exit_status_in_signal();
	// rl_replace_line("", 0); // プロンプトのバッファをクリア
	// rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	// rl_redisplay();         // プロンプトを再描画
	exit(EXIT_FAILURE);
}

static void	set_sigint_handler_during_heredoc(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_during_heredoc;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

static void set_sigquit_handler_during_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler_during_heredoc(void)
{
	set_sigint_handler_during_heredoc();
	set_sigquit_handler_during_heredoc();
}

