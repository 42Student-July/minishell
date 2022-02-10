/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:59 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/18 17:32:00 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*dest;
	unsigned char	chr;
	size_t			i;

	i = 0;
	dest = (unsigned char *)buf;
	chr = (unsigned char)ch;
	while (i < n)
	{
		dest[i] = chr;
		i++;
	}
	return (dest);
}
