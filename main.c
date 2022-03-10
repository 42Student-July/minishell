#include "lexer.h"
#include "libft.h"
#include "repl.h"
#include "sigaction.h"
#include "common.h"

int	g_exit_status = 0;
t_mem_mgt	g_mem_mgt = {NULL, 0, 0};

int main()
{
	set_signal_handler_during_command();
	start_repl();
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
