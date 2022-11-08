#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	void	*new;

	s_len = ft_strlen(s) + 1;
	if (!(new = malloc(s_len)))
		return (NULL);
	return ((char *)ft_memcpy(new, s, s_len));
}
