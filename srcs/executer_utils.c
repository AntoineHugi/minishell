#include "../includes/minishell.h"

void	restore_stdin(t_command *cmd)
{
	dup2(cmd->og_stdin, STDIN_FILENO);
	dup2(cmd->og_stdout, STDOUT_FILENO);
}

int	save_stdin(t_command *cmd)
{
	cmd->og_stdin = dup(STDIN_FILENO);
	if (cmd->og_stdin == -1)
		return (0);
	cmd->og_stdout = dup(STDOUT_FILENO);
	if (cmd->og_stdout == -1)
		return (0);
	return (1);
}
