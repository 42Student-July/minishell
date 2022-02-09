/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:26:01 by akito             #+#    #+#             */
/*   Updated: 2021/09/09 18:26:02 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	index = 0;
	while (big[index] != '\0' && index < len)
	{
		j = 0;
		while (little[j] != '\0' && index + j < len
			&& big[index + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[index]);
		index++;
	}
	return (NULL);
}
