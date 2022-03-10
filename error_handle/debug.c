
#include "error_handle.h"

void	print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("line : %s\n", array[i]);
		i++;
	}
	printf("line_count = %zu\n", i);
}
