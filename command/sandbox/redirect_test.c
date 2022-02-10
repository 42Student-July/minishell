#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	char *infile = NULL;
	char *outfile = NULL;
	char **command = (char **)malloc(sizeof(char *) * 1000);
	int	i;
	pid_t	cpid;
	int status;

	i = 1;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "<") == 0)
		{
			infile = strdup(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], ">") == 0)
		{
			outfile = strdup(argv[i + 1]);
			i++;
		}
		else
		{
			command[i - 1] = strdup(argv[i]);
			i++;
		}
	}
	if ((cpid = fork()) == -1) {
		perror("fork");
	}
	else if (cpid == 0)
	{
		if (infile != NULL)
		{
			close(0);
			if (open(infile, O_RDONLY) == -1)
			{
				perror(infile);
				exit(1);
			}
		}
		if (outfile != NULL)
		{
			close(1);
			if (open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666) == -1)
			{
				perror(outfile);
				exit(1);
			}
		}
		i = 0;
		execvp(command[0], command);
		exit(1);
	}
	if (wait(&status) == (pid_t)-1) {
		perror("wait");
		exit(1);
	}
	return 0;
}
