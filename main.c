#include "lexer.h"
#include "libft.h"
#include "repl.h"
#include "sigaction.h"
#include "common.h"
#include "libmem_mgt/mem_mgt.h"
#include "libmem_mgt/replace_mem_mgt.h"

int	g_exit_status = 0;

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	set_signal_handler_during_command();
	start_repl();
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q minishell");
}
