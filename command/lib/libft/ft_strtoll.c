/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:29:40 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 20:54:56 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char a)
{
	if (a == '\t' || a == '\n' || a == '\v'
		|| a == ' ' || a == '\r' || a == '\f' )
		return (1);
	return (0);
}

long long	ft_strtoll(const char *str, int *status)
{
	size_t		i;
	long long	num;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((num * 10 + (str[i] - '0')) / 10 != num)
			*status = false;
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		*status = false;
	return ((num * sign));
}
