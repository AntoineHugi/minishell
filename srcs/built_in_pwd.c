#include "../includes/minishell.h"

void	print_wd(t_command *cmd)
{
	char	cwd[1024];

	/*if (cmd->full_cmd_args[1])
		print_error("no arguments allowed for pwd", 1);*/
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		cmd_error(cmd, strerror(errno), errno);
}
