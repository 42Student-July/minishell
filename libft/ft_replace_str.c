/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:36:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/06 00:10:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static char	*cat_str3(char *work, const char *replace, char *tmp)
{
	char	*ret;
	char	*tmp_join;

	tmp_join = ft_strjoin(work, replace);
	if (tmp_join == NULL)
	{
		free(work);
		free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(tmp_join, tmp);
	free(work);
	free(tmp);
	free(tmp_join);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

char	*ft_replace_str(const char *src, const char *target, \
						const char *replace)
{
	char	*work;
	char	*tmp;
	char	*p;

	work = ft_strdup(src);
	if (work == NULL)
		return (NULL);
	p = ft_strnstr(work, target, ft_strlen(work));
	if (p == NULL)
		return (work);
	*p = '\0';
	p += ft_strlen(target);
	tmp = ft_strdup(p);
	if (tmp == NULL)
	{
		free(work);
		return (NULL);
	}
	return (cat_str3(work, replace, tmp));
}
