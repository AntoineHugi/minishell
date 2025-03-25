#include "../includes/minishell.h"

void	print_env(t_command *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	cmd->exit_status = 0;
}
