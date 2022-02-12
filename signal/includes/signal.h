/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:34:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/12 14:26:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>

// set_signal.c

void	set_interactive_sigint(void);
void	set_dfl_sigint(void);
void	set_dfl_sigquit(void);

// sigaction.c

void	interactive_sigint(int sig, siginfo_t *info, void *ucontext);
void	dfl_sigint(int sig, siginfo_t *info, void *ucontext);
void	dfl_sigquit(int sig, siginfo_t *info, void *ucontext);

#endif