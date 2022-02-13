/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:57:59 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/13 01:23:45 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

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

void	set_interactive_signal(void)
{
	set_interactive_sigint();
	signal(SIGQUIT, SIG_IGN);
}

void	set_dfl_signal(void)
{
	set_dfl_sigint();
	set_dfl_sigquit();
}
