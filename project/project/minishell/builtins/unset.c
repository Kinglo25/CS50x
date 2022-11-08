#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static int	comp(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (1);
	while (n--)
	{
		if (*s1 != *s2 && !*s2 && *s1 == '=')
			return (0);
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (!*s1)
			return (1);
		s1++;
		s2++;
	}
	return (1);
}

static void	ret_malloc(char ***ret, int i)
{
	*ret = malloc(sizeof(char *) * i);
	if (!(*ret))
		return (exit(0));
}

int	ft_unset(char ***env, char **cmd)
{
	int		i;
	int		j;
	char	**ret;

	j = 0;
	while (cmd[++j])
	{
		i = 0;
		while ((*env)[i])
			i++;
		ret_malloc(&ret, i);
		i = -1;
		while (comp((*env)[++i], cmd[j], ft_strlen(cmd[1]) + 1) && (*env)[i])
			ret[i] = (*env)[i];
		if (!(*env)[i])
			return (free(ret), 1);
		free((*env)[i]);
		while ((*env)[++i])
			ret[i - 1] = (*env)[i];
		ret[i - 1] = NULL;
		free(*env);
		*env = ret;
	}
	return (1);
}
