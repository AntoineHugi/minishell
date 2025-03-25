#include "../includes/minishell.h"

void	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	cmd_error(t_command *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	write(2, msg, ft_strlen(msg));
	if (err_num == 127)
		write(2, ": command not found", 20);
	write(2, "\n", 1);
	free_all_cmds(cmd);
	exit (err_num);
}

void	export_error(t_command *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	write(2, cmd->full_cmd_args[1], ft_strlen(cmd->full_cmd_args[1]));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_all_cmds(cmd);
	exit (err_num);
}
