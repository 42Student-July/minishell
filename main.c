#include "lexer.h"
#include "libft.h"
#include "repl.h"
#include "sigaction.h"
#include "common.h"

int	g_exit_status = 0;

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	set_dfl_signal();
	start_repl();
}
