/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:18:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/12 14:22:31 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	interactive_sigint(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	printf("\n");
	rl_replace_line("", 0); // プロンプトのバッファをクリア
	rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	rl_redisplay();         // プロンプトを再描画
}

void	dfl_sigint(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	g_fin_status = 1;
}

void	dfl_sigquit(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	printf("Quit: 3\n");
}
