#include "sigaction.h"

static void	set_sigint_handler_default(void)
{
	signal(SIGINT, SIG_DFL);
}

static void	set_sigquit_handler_default(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	reset_signal_handler(void)
{
	set_sigint_handler_default();
	set_sigquit_handler_default();
}
