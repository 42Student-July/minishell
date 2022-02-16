#include "libft.h"
#include <stdio.h>

static long long	ft_atoll(const char *str)
{
	size_t		i;
	long long	num;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (!str)
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

long	ft_atol(const char *str)
{
	long long	num;

	num = ft_atoll(str);
	return (num);
}

int main()
{
	printf("%ld\n", ft_atol("11"));
}
