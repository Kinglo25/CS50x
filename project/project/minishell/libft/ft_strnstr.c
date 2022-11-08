#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		needle_len;

	if (!*needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && len)
	{
		if (*haystack == *needle && len >= needle_len)
			if (!ft_strncmp(haystack, needle, needle_len))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
