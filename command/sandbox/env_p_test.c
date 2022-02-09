/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_p_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:07:04 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/03 20:35:18 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, char **argv, char **envp)
{
	char **env = envp;

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
	printf("environ = %p\n", envp);
	printf("*env : %s\n", *env);
	return 0;
}
