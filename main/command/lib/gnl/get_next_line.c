/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:49:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/01/20 20:42:56 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffering(char **text, int *status, ssize_t text_len)
{
	ssize_t	index;
	char	*tmp;
	char	*ret;

	ret = NULL;
	*status = 1;
	if (*text == NULL)
		return (NULL);
	while ((*text)[text_len] != '\0')
		text_len++;
	index = ft_strchr_index(*text, '\n');
	if (index != -1)
	{
		tmp = ft_substr_gnl(*text, index + 1, text_len - (index + 1), status);
		if (tmp != NULL)
		{
			(*text)[index + 1] = '\0';
			ret = *text;
			*text = tmp;
		}
		else
			*status = -1;
	}
	return (ret);
}

char	*finish(char **text, char *read_res, int *status, int read_count)
{
	ssize_t	index;
	char	*ret;
	size_t	text_len;

	text_len = 0;
	free(read_res);
	ret = NULL;
	if (read_count < 0)
		*status = -1;
	if (*text == NULL)
		return (NULL);
	while ((*text)[text_len] != '\0')
		text_len++;
	index = ft_strchr_index(*text, '\n');
	if (index == -1)
	{
		if (text_len != 0)
			ret = ft_strdup_gnl(*text, status);
		else
			free(*text);
		*text = NULL;
	}
	return (ret);
}

char	*ret_nl(char *read_res, char **text, int *status, char *tmp)
{
	size_t	tmp_len;

	tmp_len = 0;
	while (tmp[tmp_len] != '\0')
		tmp_len++;
	if (tmp_len == 0)
		free(tmp);
	if (*text != NULL)
	{	
		read_res = ft_strjoin_gnl(*text, read_res);
		if (read_res == NULL)
			*status = -1;
		if (tmp_len == 0)
			*text = NULL;
		else
			*text = tmp;
	}
	if (tmp_len == 0 || *text != NULL)
		return (read_res);
	*text = ft_strdup_gnl(tmp, status);
	if (*text != NULL)
		return (read_res);
	free(read_res);
	return (NULL);
}

char	*store_buffer(char *read_res, char **text, int *status, ssize_t res_len)
{
	char	*tmp;

	*status = 1;
	res_len = 0;
	if (ft_strchr_index(read_res, '\n') != -1)
	{
		while (read_res[res_len] != '\0')
			res_len++;
		tmp = ft_substr_gnl(read_res, ft_strchr_index(read_res, '\n') + 1, \
			res_len - (ft_strchr_index(read_res, '\n') + 1), status);
		if (tmp != NULL)
		{	
			read_res[ft_strchr_index(read_res, '\n') + 1] = '\0';
			return (ret_nl(read_res, text, status, tmp));
		}
		*status = -1;
		return (NULL);
	}
	if (*text == NULL)
		*text = ft_strdup_gnl(read_res, status);
	else
		*text = ft_strjoin_gnl(*text, read_res);
	if (*text == NULL)
		*status = -1;
	return (NULL);
}

char	*get_next_line(int fd, int *status)
{
	static char	*text;
	char		*ret;
	char		*read_res;
	ssize_t		read_count;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	read_count = 0;
	ret = read_buffering(&text, status, read_count);
	while (1)
	{
		if (*status == -1 && ret == NULL)
			return (NULL);
		if (*status == 1 && ret != NULL)
			return (ret);
		read_res = NULL;
		read_res = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
		read_count = read(fd, read_res, BUFFER_SIZE);
		if (read_count <= 0)
			return (finish(&text, read_res, status, read_count));
		*(read_res + read_count) = '\0';
		ret = store_buffer(read_res, &text, status, read_count);
	}
}
