#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>

int	main()
{
	int	i;
	pid_t	cpid;

	i = 0;
	if ((cpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (cpid == 0)
	{
		while (i < 10)
		{
			printf("child i = %d\n", i);
			fflush(stdout);
			sleep(1);
			i++;
		}
		exit(0);
	}
	i = 10;
	while (i >= 0)
	{
		printf("parent i = %d\n", i);
		fflush(stdout);
		sleep(1);
		i--;
	}
	putchar('\n');
	return (0);
}