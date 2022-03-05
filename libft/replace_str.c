/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:36:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/05 16:41:44 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main()
{
	char src[100] = "1. this is a test.";
	char *replace = "t";
	char *target  = "|";
	char *result;

	str_replace(src, replace, target, &result);
	printf("%s\n", result); // => "1. |his is a |es|."
	free(result);
	return 0;
}
