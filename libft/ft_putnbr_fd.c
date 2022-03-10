
#include "libft.h"
static void	put_digit_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long long	nb;

	nb = (long long)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd((int)(nb / 10), fd);
		put_digit_fd((int)(nb % 10), fd);
	}
	if (nb < 10)
	{
		put_digit_fd((int)nb, fd);
	}
}

static void	put_digit_fd(int n, int fd)
{
	ft_putchar_fd(n + '0', fd);
}
