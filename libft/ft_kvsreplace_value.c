/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvsreplace_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:39:13 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/24 17:18:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kvsreplace_value(void *content, char *new_value)
{
	t_kvs	*k;
	char	*tmp;

	k = (t_kvs *)content;
	tmp = k->value;
	k->value = new_value;
	free(tmp);
}
