/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:16:17 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/03 19:56:40 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_format(va_list *ap, const char *fmt)
{
	fmt++;
	if (*fmt == 'c')
		return (ft_print_c(va_arg(*ap, int)));
	else if (*fmt == 's')
		return (ft_print_s(va_arg(*ap, char *)));
	else if (*fmt == 'p')
		return (ft_print_p(va_arg(*ap, unsigned long)));
	else if (*fmt == 'd' || *fmt == 'i')
		return (ft_print_d_and_u(va_arg(*ap, int), 0));
	else if (*fmt == 'u')
		return (ft_print_d_and_u(va_arg(*ap, unsigned int), 0));
	else if (*fmt == 'x')
		return (ft_print_x(va_arg(*ap, unsigned int)));
	else if (*fmt == 'X')
		return (ft_print_lx(va_arg(*ap, unsigned int)));
	else if (*fmt == '%')
		return (ft_print_percent());
	else
		return (-1);
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	long	count;
	long	res;

	va_start(ap, fmt);
	if (fmt == NULL)
		return (-1);
	count = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			res = ft_put_format(&ap, fmt++);
			if (res == -1)
				return (res);
			count += res;
		}
		else
			count += ft_print_c(*fmt);
		if (count >= INT_MAX)
			return (-1);
		fmt++;
	}
	va_end(ap);
	return (count);
}
