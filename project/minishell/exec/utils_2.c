#include "minishell.h"
#include "builtins.h"
#include "exec.h"

void	dup_and_close_pipe(int end, int fd, int *ends)
{
	my_dup(end, fd);
	close_pipe(ends);
}

int	check_for_bin(t_mini *shell)
{
	char	**cmd;
	t_here	*doc;

	cmd = shell->cmds[0].av;
	doc = shell->cmds[0].redir_in.doc;
	if (!bin_normalise(cmd))
		return (1);
	else
		if (ft_bin_solo(cmd, &shell->env, doc) == 1)
			return (1);
	return (0);
}
