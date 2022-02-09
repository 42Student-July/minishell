/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putpointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:43:02 by akito             #+#    #+#             */
/*   Updated: 2021/09/12 12:43:06 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_my_putpointer(size_t n)
{
	int64_t	cnt;

	cnt = ft_my_putstr("0x");
	cnt += ft_my_putbase(n, "0123456789abcdef");
	return ((int64_t)cnt);
}
