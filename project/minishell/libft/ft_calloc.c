#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*calloc;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (!(calloc = malloc(nmemb * size)))
		return (NULL);
	ft_bzero(calloc, nmemb * size);
	return (calloc);
}
