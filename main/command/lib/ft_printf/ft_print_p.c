/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 17:15:22 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/03 19:44:38 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(unsigned long hex)
{
	char	*result;

	if (hex == 0)
		return (ft_put_zero());
	result = ft_convert_dec_to_hexstr(hex);
	return (ft_putres(result, NORMAL_MODE));
}

int	ft_print_p(unsigned long ptr)
{
	int	digits;

	digits = 2;
	ft_putstr("0x");
	digits += ft_puthex(ptr);
	return (digits);
}
