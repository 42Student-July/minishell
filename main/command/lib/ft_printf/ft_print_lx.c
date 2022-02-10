/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:57:09 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/03 19:52:35 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_lx(unsigned int hex)
{
	char	*result;

	if (hex == 0)
		return (ft_put_zero());
	result = ft_convert_dec_to_hexstr(hex);
	if (!result)
		return (0);
	return (ft_putres(result, UPPER_MODE));
}
