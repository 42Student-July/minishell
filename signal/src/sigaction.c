/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:18:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/23 14:17:01 by tkirihar         ###   ########.fr       */
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

