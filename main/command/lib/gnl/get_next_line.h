/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:55:27 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/20 20:39:06 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*read_buffering(char **text, int *status, ssize_t text_len);
char	*get_next_line(int fd, int *status);
char	*store_buffer(	char *read_res, char **text, \
						int *status, ssize_t res_len);
char	*ret_nl(char *read_res, char **text, int *status, char *tmp);
char	*finish(char **text, char *read_res, int *status, int read_count);
ssize_t	ft_strchr_index(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dest, const char *src, size_t size);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int *status);
char	*ft_strdup_gnl(char *src, int *status);

#endif
