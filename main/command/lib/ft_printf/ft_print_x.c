/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:54:31 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/03 19:52:42 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x(unsigned int hex)
{
	char	*result;

	if (hex == 0)
		return (ft_put_zero());
	result = ft_convert_dec_to_hexstr(hex);
	if (!result)
		return (0);
	return (ft_putres(result, NORMAL_MODE));
}
