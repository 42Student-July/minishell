/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:34:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/13 01:22:57 by tkirihar         ###   ########.fr       */
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

# define ABC 1

int	g_exit_status;

// set_signal.c

void	set_interactive_sigint(void);
void	set_dfl_sigint(void);
void	set_dfl_sigquit(void);
void	set_interactive_signal(void);
void	set_dfl_signal(void);

// sigaction.c

void	interactive_sigint(int sig);
void	dfl_sigint(int sig);
void	dfl_sigquit(int sig);

#endif