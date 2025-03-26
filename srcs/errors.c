#include "../includes/minishell.h"

void	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	cmd_error(t_command *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	convert_exit_status(&errno);
	write(2, msg, ft_strlen(msg));
	if (err_num == 127)
		write(2, ": command not found", 20);
	write(2, "\n", 1);
	free_all_cmds(cmd);
	exit (err_num);
}

void	file_error(t_command *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	convert_exit_status(&errno);
	write(2, msg, ft_strlen(msg));
	if (err_num == 500)
	{
		write(2, ": Is a directory", 17);
		err_num = 126;
	}
	write(2, "\n", 1);
	free_all_cmds(cmd);
	exit (err_num);
}
