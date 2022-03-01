/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:34:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/17 23:15:21 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
