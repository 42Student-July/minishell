/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:47:34 by akito             #+#    #+#             */
/*   Updated: 2021/09/12 15:20:22 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putstr(const char *str)
{
	if (str == NULL)
		return (ft_my_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}
