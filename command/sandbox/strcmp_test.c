#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "../includes/command.h"

int	main()
{
	printf("_ = %d\n", '_');
	printf("a = %d\n", 'a');
	printf("ft_strncmp(PWD) = %d\n", ft_strncmp("PWD", "eeeee", 3));
	return (0);
}