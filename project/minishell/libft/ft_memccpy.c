#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
		if ((*(char*)dest++ = *(char*)src++) == (char)c)
			return (dest);
	return (0);
}
