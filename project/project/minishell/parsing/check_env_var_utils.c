#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	smlp(char c, int *macro_len)
{
	if (c == '?')
		return (*macro_len = 1);
	return (0);
}
