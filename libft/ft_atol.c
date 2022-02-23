#include "libft.h"
#include <stdio.h>
#include <limits.h>

static void	read_sign(int *sign, size_t *i, char c)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		(*i)++;
	}
}

bool 	ft_atol(const char *nptr, long *num)
{
	size_t		i;
	int			sign;

	*num = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (!ft_strncmp(nptr, "-9223372036854775808", 20) \
		&& ft_strlen(nptr) == 20)
	{
		*num = LONG_MIN;
		return (true);
	}
	read_sign(&sign, &i, nptr[i]);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		*num = (*num * 10) + (nptr[i] - '0');
		if (*num < 0)
			return (false);
		i++;
	}
	*num *= sign;
	return (true);
}

// int main()
// {
// 	long	exit_status;
// 	bool	 flag;
// 	flag = ft_atol("-922337", &exit_status);
// 	printf("%d\n", flag);
// 	printf("%ld\n", exit_status);
// }
