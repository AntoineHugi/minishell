#include "../includes/minishell.h"

void	print_env(t_command *cmd, char **envp)
{
	int	i;

	if (cmd->full_cmd_args[1])
		print_error("no arguments allowed for env", 1);
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
