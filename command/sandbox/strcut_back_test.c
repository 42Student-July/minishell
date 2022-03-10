
#include "../../libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>

int	main()
{
	char *a;
	
	a = ft_strdup("/Users/masashi/Projects/42tokyo/minishell/test/test_sh");
	printf("ft_strcut_back(a, '/') : %s\n", ft_strcut_back(a, '/'));
	
	
	return (0);
}
