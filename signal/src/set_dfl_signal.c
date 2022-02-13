/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_def_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:36:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/13 16:42:08 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

static void	set_dfl_sigint(void)
{
	struct sigaction	act;

	act.sa_handler = dfl_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

static void	set_dfl_sigquit(void)
{
	struct sigaction	act;

	act.sa_handler = dfl_sigquit;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
}

void	set_dfl_signal(void)
{
	set_dfl_sigint();
	set_dfl_sigquit();
}
