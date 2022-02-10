/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:25:47 by akito             #+#    #+#             */
/*   Updated: 2021/09/09 18:25:48 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < size - dst_len)
		ft_memmove(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memmove(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
