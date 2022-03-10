
#ifndef SIGACTION_H
# define SIGACTION_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "common.h"

// set_signal_handler_during_command.c

void	set_signal_handler_during_command(void);

// set_signal_handler_during_readline.c

void	set_signal_handler_during_readline(void);

// set_signal_handler_during_heredoc.c
void	set_signal_handler_during_heredoc(void);

// reset_signal_handler.c
void	reset_signal_handler(void);
#endif
