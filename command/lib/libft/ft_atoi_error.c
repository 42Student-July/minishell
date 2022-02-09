/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:27:52 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 20:59:19 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_error(const char *str, int *status)
{
	long long	ret;

	*status = true;
	if (ft_strlen(str) == 0)
		*status = false;
	if (ft_strlen(str) == 1)
		if (*str == '+' || *str == ' ' || *str == '-')
			*status = false;
	if (*str == '0')
		if (ft_strlen(str) != 1)
			*status = false;
	if (*status == false)
		return (0);
	ret = ft_strtoll(str, status);
	if (ret > INT_MAX || ret < INT_MIN)
	{
		*status = false;
		return (0);
	}
	return ((int)ret);
}
