#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdint.h>

void	*ft_xcalloc(size_t nmemb, size_t size)
{
	void	*res;

	if (size == 0 || nmemb == 0)
	{
		size = 1;
		nmemb = 1;
	}
	if (nmemb > (SIZE_MAX / size))
	{
		errno = ENOMEM;
		return (NULL);
	}
	res = (void *)ft_xmalloc(nmemb * size);
	ft_bzero(res, size * nmemb);
	return (res);
}
