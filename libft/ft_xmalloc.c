#include "libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*ret;
	
	ret = malloc(size);
	if (ret == NULL)
	{
		perror(ret);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
