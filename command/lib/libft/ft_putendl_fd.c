/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:32:07 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/18 17:32:08 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (len > STR_BUFF_SIZE)
	{
		write(fd, s + i, STR_BUFF_SIZE);
		i = i + STR_BUFF_SIZE;
		len = len - STR_BUFF_SIZE;
	}
	write(fd, s + i, len);
	write(fd, "\n", 1);
}
