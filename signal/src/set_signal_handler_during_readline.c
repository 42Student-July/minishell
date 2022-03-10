
#include "sigaction.h"

/* SIGINT */
void	handle_sigint_during_readline(int sig)
{
	(void)sig;
	g_exit_status = 1;
	printf("\n");
	// print_exit_status_in_signal();
	rl_replace_line("", 0); // プロンプトのバッファをクリア
	rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	rl_redisplay();         // プロンプトを再描画
}

static void	set_sigint_handler_during_readline(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_during_readline;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

static void set_sigquit_handler_during_readline(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler_during_readline(void)
{
	set_sigint_handler_during_readline();
	set_sigquit_handler_during_readline();
}
