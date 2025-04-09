#include "../includes/minishell.h"

void	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	cmd_error(t_cmd *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	err_num = convert_exit_status(err_num);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (err_num == 127)
		write(STDERR_FILENO, ": command not found", 20);
	write(STDERR_FILENO, "\n", 1);
	free_all_cmds(cmd);
	rl_clear_history();
	exit (err_num);
}

void	file_error(t_cmd *cmd, char *msg, int err_num)
{
	restore_stdin(cmd);
	err_num = convert_exit_status(err_num);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (err_num == 200)
	{
		write(STDERR_FILENO, ": Is a directory", 17);
		err_num = 126;
	}
	write(STDERR_FILENO, "\n", 1);
	free_all_cmds(cmd);
	rl_clear_history();
	exit (err_num);
}

void	sig_msg(int *exit_status)
{
	if (g_status == 130)
	{
		write(1, "\n", 1);
		*exit_status = g_status;
	}
	if (g_status == 131)
	{
		write(1, "Quit (core dumped)\n", 19);
		*exit_status = g_status;
	}
}
