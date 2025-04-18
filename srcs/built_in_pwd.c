#include "../includes/minishell.h"

void	print_wd(t_cmd *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		cmd_error(cmd, strerror(errno), errno);
	cmd->exit_status = 0;
}
