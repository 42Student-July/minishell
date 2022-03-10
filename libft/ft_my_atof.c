
#include "libft.h"
#include <stdint.h>

static void		read_sign(int *sign, size_t *i, char c);
static double	ft_pow(double x, int y);

static double	get_decimal(const char *nptr)
{
	size_t	i;
	double	decimal;

	i = 0;
	decimal = 0;
	while (ft_isdigit(nptr[i]))
	{
		decimal += (nptr[i] - '0') / (ft_pow(10, i + 1));
		i++;
	}
	return (decimal);
}

double	ft_my_atof(const char *nptr)
{
	size_t	i;
	int		sign;
	double	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	read_sign(&sign, &i, nptr[i]);
	while (ft_isdigit(nptr[i]))
	{
		result += 10 * result + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
	{
		result += get_decimal(&nptr[i + 1]);
	}
	return (result * sign);
}

static void	read_sign(int *sign, size_t *i, char c)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		(*i)++;
	}
}

static double	ft_pow(double x, int y)
{
	if (y == 0)
		return (1);
	if (y > 0)
		return (x * ft_pow(x, y - 1));
	if (y < 0)
		return (1 / ft_pow(x, -y));
	return (0);
}
