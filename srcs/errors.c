#include "../includes/minishell.h"

void	print_error(char *msg, int err_num)
{
	int	i;

	i = 0;
	while (msg[i])
		write(2, &msg[i++], 1);
	if (err_num == 127)
		write(2, ": command not found", 20);
	if (err_num == 2)
		write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
	exit (err_num);
}

void	cmd_error(t_command *cmd, char *msg, int err_num)
{
	int	i;

	i = 0;
	restore_stdin(cmd);
	while (msg[i])
		write(2, &msg[i++], 1);
	if (err_num == 127)
		write(2, ": command not found", 20);
	if (err_num == 2)
		write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
	free_cmd(cmd);
	exit (err_num);
}
