#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*last;

	if (c == '\0')
		return (ft_strchr(s, c));
	last = NULL;
	while ((tmp = ft_strchr(s, c)))
	{
		last = tmp;
		s = tmp + 1;
	}
	return (last);
}
