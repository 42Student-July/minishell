
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
