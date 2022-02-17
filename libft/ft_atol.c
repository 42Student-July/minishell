#include "libft.h"
#include <stdio.h>
#include <limits.h>

long 	ft_atol(const char *nptr)
{
	size_t		i;
	long long	num;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		if (num < 0)
			printf("overflow\n");
		i++;
	}
	return (num * sign);
}

int main()
{
	// int status;
	// status = 0;
	long	exit_status;
	exit_status = ft_atol("-9223372036854775808");
	printf("%ld\n", exit_status);
	printf("%ld\n", LONG_MIN);
}
