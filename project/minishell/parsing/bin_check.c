#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static	int	dup_from(char **s1, int from)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(*s1) - from + 1));
	if (!ret)
		return (0);
	while ((*s1)[from])
		ret[i++] = (*s1)[from++];
	ret[i] = '\0';
	free(*s1);
	*s1 = ret;
	return (1);
}

int	bin_normalise(char **str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	if ((*str)[0] == '/')
	{
		if (!access(*str, 0))
		{
			len = ft_strlen((str)[0]);
			while ((*str)[len] != '/')
				len--;
			if (!dup_from(str, ++len))
				return (1);
		}
		else
		{
			error_mess(NULL, *str, ": No such file or directory", 2);
			return (0);
		}
	}
	return (1);
}
