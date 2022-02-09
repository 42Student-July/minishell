/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:08:26 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/21 16:24:18 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define BASE "0123456789abcdef"
# define MAX_LEN 100
# define STR_BUFF_SIZE 1000000
# define NORMAL_MODE 0
# define UPPER_MODE 1

int		ft_printf(const char *fmt, ...);
int		ft_print_c(char c);
int		ft_print_s(char *s);
int		ft_print_d_and_u(long nb, int digits);
int		ft_print_u(unsigned long nb, int digits);
int		ft_print_p(unsigned long ptr);
int		ft_print_x(unsigned int hex);
int		ft_print_lx(unsigned int hex);
int		ft_print_percent(void);
char	*ft_convert_dec_to_hexstr(unsigned long dec);
int		ft_put_zero(void);
size_t	ft_putstr(char *s);
size_t	ft_putstr(char *s);
int		ft_toupper(int c);
int		ft_putres(char *result, int type);
size_t	ft_strlen_pf(const char *str);
void	*ft_calloc_pf(size_t count, size_t size);
void	ft_putchar_fd_pf(char c, int fd);
void	ft_bzero_pf(void *s, size_t n);
void	*ft_memset_pf(void *buf, int ch, size_t n);

#endif
