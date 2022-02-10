/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:30:15 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/18 17:30:16 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nblen(long nb)
{
	size_t		len;

	len = 0;
	if (nb == 0)
	{
		len++;
	}
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*zero(char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	size_t	i;

	n = nb;
	i = nblen(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		return (zero(str));
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[i] = '\0';
	while (n > 0)
	{
		str[--i] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}
