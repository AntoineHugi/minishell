#include "../includes/minishell.h"

void	run_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
void	run_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	char	*line;
	int		fd;

	check_input_output(cmd, tmp_fd);
	if (access(cmd->full_cmd_args[0], X_OK) == 0
		&& access(cmd->full_cmd_args[0], R_OK == 0))
	{
		fd = open(cmd->full_cmd_args[0], O_RDONLY);
		line = get_next_line(fd);
		while (line)
		{
			process_input(line, envp, exit_status);
			line = get_next_line(fd);
		}
	}
	else
	{
		execve(cmd->full_cmd_args[0], cmd->full_cmd_args, envp);
		file_error(cmd, " Permission denied", 126);
	}
	restore_stdin(cmd);
	*exit_status = cmd->exit_status;
	free_cmd(cmd);
}
