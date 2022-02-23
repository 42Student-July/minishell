/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:18:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/23 14:08:31 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

// デバッグ用の関数
void	print_exit_status_in_signal()
{
	if (g_exit_status == 0)
		printf("%d ", g_exit_status);
	else
		printf("%d ", g_exit_status);
}

void	interactive_sigint(int sig)
{
	(void)sig;
	g_exit_status = 1;
	printf("\n");
	// print_exit_status_in_signal();
	rl_replace_line("", 0); // プロンプトのバッファをクリア
	rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	rl_redisplay();         // プロンプトを再描画
}

void	dfl_sigint(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_status = 130;
}

void	dfl_sigquit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
	g_exit_status = 131;
}
