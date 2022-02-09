/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_unsigned_putnbr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:43:22 by akito             #+#    #+#             */
/*   Updated: 2021/09/12 12:43:23 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
static char	*recursive_setnbr(long long nbr, char *res);
static int	count_digits(long long nbr);

int64_t	ft_my_unsigned_putnbr(unsigned int n)
{
	long long	nbr;
	char		*res;
	int			digit_size;

	nbr = (unsigned long long)n;
	digit_size = count_digits(nbr);
	res = (char *)ft_calloc(digit_size + 1, sizeof(char));
	if (res == NULL)
		return (0);
	recursive_setnbr(nbr, res);
	ft_putstr_fd(res, 1);
	free(res);
	return ((int64_t)digit_size);
}

static int	count_digits(long long nbr)
{
	int	str_size;

	str_size = 1;
	while (nbr >= 10)
	{
		str_size++;
		nbr /= 10;
	}
	return (str_size);
}

static char	*recursive_setnbr(long long nbr, char *res)
{
	if (nbr < 10)
	{
		res[0] = nbr + '0';
		return (res + 1);
	}
	res = recursive_setnbr((nbr / 10), res);
	res[0] = (nbr % 10) + '0';
	return (res + 1);
}
