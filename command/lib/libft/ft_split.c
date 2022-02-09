/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:32:18 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/18 17:32:19 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all_strs(char **result)
{
	size_t	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static size_t	calc_array_size(char const *str, char c)
{
	size_t	size;
	int		state;
	size_t	i;

	i = 0;
	size = 0;
	state = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			size++;
		}
		i++;
	}
	return (size);
}

static size_t	calc_start_point(char const *str, char sep, size_t start)
{
	size_t	size;
	int		state;
	size_t	i;

	i = 0;
	size = 0;
	state = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == sep)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			size++;
		}
		if (size == start + 1)
			return (i);
		i++;
	}
	return (i);
}

static char	*get_str(char const *str, char sep, size_t skipcount)
{
	char	*new_str;
	size_t	start;
	size_t	len;

	len = 0;
	start = calc_start_point(str, sep, skipcount);
	while (str[start + len] != sep && str[start + len] != '\0')
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + start, len + 1);
	return (new_str);
}

char	**ft_split(char const *str, char sep)
{
	char	**result;
	size_t	size;
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	size = calc_array_size(str, sep);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	while (i < size)
	{
		result[i] = get_str(str, sep, i);
		if (result[i] == NULL)
			return (free_all_strs(result));
		i++;
	}
	result[i] = NULL;
	return (result);
}
