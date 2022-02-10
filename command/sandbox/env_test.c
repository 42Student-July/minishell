/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:07:04 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/03 17:13:34 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, char **argv)
{
	extern char	**environ;
	char **env = environ;

	while (*env)
	{
		const char *val;
		val = *env;
		if (val) {
			printf("%s\n", val);
		}
		env++;
	}
	// env -i をしたときは、environのポインタは存在するが、*envはnullになる。
	printf("environ = %p\n", environ);
	printf("*env : %s\n", *env);
	return 0;
}
