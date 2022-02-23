/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:15:09 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/21 16:46:15 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 後ろから特定の文字を探し、存在した場合その文字を含めたそれ以降の文字をcutする
char	*ft_strcut_back(char *str, char c)
{
	char	*position;
	char	*tmp;
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	tmp = str;
	position = ft_strrchr(str, c);
	if (position == NULL)
		return (NULL);
	while (tmp++ != position)
		i++;
	return (ft_substr(str, 0, i));
}

