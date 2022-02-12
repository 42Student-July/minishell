/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:57:59 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/13 00:26:42 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"
// #include "../includes/signal.h"
// # include <signal.h>

void	set_interactive_sigint(void)
{
	struct sigaction	act;

	act.sa_handler = interactive_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	set_dfl_sigint(void)
{
	struct sigaction	act;

	act.sa_handler = dfl_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	set_dfl_sigquit(void)
{
	struct sigaction	act;

	act.sa_handler = dfl_sigquit;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
}
