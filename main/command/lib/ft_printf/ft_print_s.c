/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:54:31 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 16:23:05 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(char *s)
{
	if (s == NULL)
		return (ft_putstr("(null)"));
	if (ft_strlen_pf(s) >= INT_MAX)
		return (INT_MAX);
	return (ft_putstr(s));
}
