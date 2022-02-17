#include "libft.h"
#include <stdio.h>
#include <limits.h>

long long	ft_atoll(const char *str)
{
	size_t		i;
	long long	num;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

long	ft_atol(const char *str, int *status)
{
	long long	num;

	num = ft_atoll(str);
	*status = 0;
	printf("long_max: %lld\n", LONG_LONG_MAX);
	printf("num:      %lld\n", num);
	if (num < LONG_MIN || LONG_MAX < num)
	{
		printf("flag\n");
		*status = 1;
	}
	return ((long)num);
}

int main()
{
	int status;
	status = 0;
	printf("%ld\n", ft_atol("1111111111111111111", &status));
	printf("%d\n", status);
}
