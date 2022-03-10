
#include "libft.h"
#include <limits.h>
static char	*recursive_setnbr(uint64_t nbr, char *res, char *base);
static int	count_digits(uint64_t nbr, char *base);

int64_t	ft_my_putbase(size_t n, char *base)
{
	uint64_t	nbr;
	char		*res;
	int			digit_size;

	nbr = (uint64_t) n;
	digit_size = count_digits(nbr, base);
	res = (char *)ft_calloc(digit_size + 1, sizeof(char));
	if (res == NULL)
		return (0);
	recursive_setnbr(nbr, res, base);
	digit_size = ft_my_putstr(res);
	free(res);
	return ((int64_t)digit_size);
}

static int	count_digits(uint64_t nbr, char *base)
{
	int				str_size;
	const uint64_t	base_len = ft_strlen(base);

	str_size = 1;
	while (nbr >= base_len)
	{
		str_size++;
		nbr /= base_len;
	}
	return (str_size);
}

static char	*recursive_setnbr(uint64_t nbr, char *res, char *base)
{
	const uint64_t	base_len = ft_strlen(base);

	if (nbr < base_len)
	{
		res[0] = base[nbr];
		return (res + 1);
	}
	res = recursive_setnbr((nbr / base_len), res, base);
	res[0] = base[nbr % base_len];
	return (res + 1);
}
