/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:43:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 21:28:59 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

bool	is_lvalue_bigger_ascii(char *lvalue, char *rvalue)
{
	size_t	llen;
	size_t	rlen;
	size_t	use_len;

	llen = ft_strlen(lvalue);
	rlen = ft_strlen(rvalue);
	if (llen > rlen)
		use_len = llen;
	else
		use_len = rlen;
	if (ft_strncmp(lvalue, rvalue, use_len) > 0)
		return (true);
	return (false);
}

bool	is_same_str(char *a, char *b)
{
	if (ft_strlen(a) != ft_strlen(b))
		return (false);
	if (ft_strncmp(a, b, ft_strlen(a)) != 0)
		return (false);
	return (true);
}
