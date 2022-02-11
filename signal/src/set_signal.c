/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:57:59 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/12 01:50:50 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	set_interactive_sigint(void)
{
	struct sigaction	act;

	act.sa_sigaction = interactive_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	set_dfl_sigint(void)
{
	struct sigaction	act;

	act.sa_sigaction = dfl_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	set_dfl_sigquit(void)
{
	struct sigaction	act;

	act.sa_sigaction = dfl_sigquit;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
}
