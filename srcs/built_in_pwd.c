#include "../includes/minishell.h"

void	print_wd(t_command *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		cmd_error(cmd, strerror(errno), errno);
}
