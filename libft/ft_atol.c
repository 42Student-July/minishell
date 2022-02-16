#include "libft.h"
#include <stdio.h>

long	ft_atol(const char *str)
{
	printf("ft_atol\n");
	return (__LONG_MAX__);
	// long	num;

	// num = ft_long_atoi(str);
	// return (INT_MIN <= num && num <= INT_MAX);
}

int main()
{
	printf("%ld\n", ft_atol("11"));
}
