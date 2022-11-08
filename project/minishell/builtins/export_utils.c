#include "minishell.h"
#include "builtins.h"
#include "exec.h"

void	realloc_env(int j, char **ret, char **env)
{
	ret[j] = ft_strdup(env[j]);
	if (!ret)
		exit(0);
	free(env[j]);
}

void	count_val(t_count *c)
{
	c->i = 0;
	c->j = -1;
}
