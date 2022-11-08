#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;

	x = (n < 0) ? -n : n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (x > 9)
		ft_putnbr_fd(x / 10, fd);
	ft_putchar_fd(x % 10 + 48, fd);
}
