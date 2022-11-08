#include "libft.h"

static int	find_n_len(unsigned int x)
{
	if (x < 10u)
		return (1);
	return (1 + find_n_len(x / 10));
}

char		*ft_itoa(int n)
{
	char			*ans;
	int				n_len;
	unsigned int	x;

	x = (n < 0) ? -n : n;
	n_len = find_n_len(x);
	if (n < 0)
		n_len++;
	if (!(ans = malloc(n_len + 1)))
		return (NULL);
	ans[n_len--] = '\0';
	if (n < 0)
		ans[0] = '-';
	if (x == 0)
		ans[0] = '0';
	while (x)
	{
		ans[n_len--] = (char)(x % 10 + 48);
		x /= 10;
	}
	return (ans);
}
