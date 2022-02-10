/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:25:14 by akito             #+#    #+#             */
/*   Updated: 2021/09/09 18:25:15 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*to;
	const unsigned char	*from;

	if (dest == NULL && src == NULL)
		return (NULL);
	to = (unsigned char *)dest;
	from = (unsigned const char *)src;
	if (from > to)
		ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i > 0)
		{
			to[i - 1] = from[i - 1];
			i--;
		}
	}
	return (dest);
}
