/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_interactive_signal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:36:42 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/13 16:42:40 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

static void	set_interactive_sigint(void)
{
	struct sigaction	act;

	act.sa_handler = interactive_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	set_interactive_signal(void)
{
	set_interactive_sigint();
	signal(SIGQUIT, SIG_IGN);
}
