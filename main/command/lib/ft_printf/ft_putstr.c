/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:57:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 16:21:35 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putstr(char *s)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen_pf(s);
	while (len > STR_BUFF_SIZE)
	{
		write(1, s + i, STR_BUFF_SIZE);
		i = i + STR_BUFF_SIZE;
		len = len - STR_BUFF_SIZE;
	}
	write(1, s + i, len);
	return (len);
}
