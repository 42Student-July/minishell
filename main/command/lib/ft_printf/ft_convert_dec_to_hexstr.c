/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_dec_to_hexstr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:04:04 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 16:20:26 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_dec_to_hexstr(unsigned long dec)
{
	char	*hexstr;
	int		i;

	hexstr = (char *)ft_calloc_pf(sizeof(char), MAX_LEN);
	if (!hexstr)
		return (NULL);
	i = 1;
	while (1)
	{
		*(hexstr + i) = BASE[dec % 16];
		i++;
		if (dec > 16)
			dec /= 16;
		else
		{
			if (dec / 16 == 1)
				*(hexstr + i) = BASE[dec / 16];
			break ;
		}
	}
	i++;
	*(hexstr + i) = '\0';
	return (hexstr);
}

int	ft_put_zero(void)
{
	ft_putchar_fd_pf('0', 1);
	return (1);
}

int	ft_putres(char *result, int type)
{
	int	digits;
	int	i;

	digits = 0;
	i = 1;
	while (result[i] != '\0')
		i++;
	i--;
	while (result[i] != '\0')
	{
		digits += 1;
		if (type == UPPER_MODE)
			ft_putchar_fd_pf(ft_toupper(result[i]), 1);
		else
			ft_putchar_fd_pf(result[i], 1);
		i--;
	}
	free(result);
	result = NULL;
	return (digits);
}
