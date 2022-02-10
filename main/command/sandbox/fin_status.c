#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../lib/libft/libft.h"

int	g_fin_status;

int	main()
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("c\n");
		sleep(5);
		exit(0);
	}
	else if (pid > 0)
	{
		printf("p\n");
		pid = wait(&status);
		if (pid == -1)
			printf("error\n");
		g_fin_status = WEXITSTATUS(status);
		printf("fin_status %d\n", g_fin_status);
	}
	return (0);
}
