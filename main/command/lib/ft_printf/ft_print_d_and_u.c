/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_and_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:54:31 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 16:20:39 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_d_and_u(long nb, int digits)
{
	long	num;

	num = nb;
	if (nb < 0)
	{
		ft_putchar_fd_pf('-', 1);
		num = num * -1;
		digits += 1;
	}
	if (num >= 10)
	{
		digits = ft_print_d_and_u(num / 10, digits);
		num = num % 10;
	}
	if (num < 10)
	{
		digits += 1;
		ft_putchar_fd_pf('0' + num, 1);
	}
	return (digits);
}
