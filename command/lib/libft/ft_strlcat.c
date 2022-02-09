/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:32:39 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 18:04:42 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dsize;
	size_t	ssize;
	size_t	total_size;
	size_t	i;
	size_t	condition;

	if (dest == NULL || src == NULL)
		return (0);
	dsize = ft_strlen((char *)dest);
	ssize = ft_strlen((char *)src);
	total_size = dsize + ssize;
	condition = size - dsize - 1;
	i = 0;
	if (dsize < size)
	{
		while (src[i] != '\0' && i < condition)
			dest[dsize++] = src[i++];
		dest[dsize] = '\0';
		return (total_size);
	}
	dest[dsize] = '\0';
	return (ssize + size);
}
