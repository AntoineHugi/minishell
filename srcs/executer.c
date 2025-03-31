#include "../includes/minishell.h"

void	assign_envp(t_command *cmd, char **envp)
{
	while (cmd)
	{
		cmd->envp = envp;
		cmd = cmd->next;
	}
}

int	convert_exit_status(int exit_status)
{
	if (exit_status > 255)
		return (exit_status >> 8);
	else
		return (exit_status);
}

static int	is_path(char *str)
{
	if (str[0] == '/')
		return (1);
	if (str[0] == '.')
	{
		if (str[1] == '/')
			return (1);
	}
	return (0);
}

static void	ex_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	pid_t		pid;
	struct stat	path_stat;

	pid = fork();
	if (pid == -1)
		file_error(cmd, strerror(errno), errno);
	else if (pid == 0)
	{
		if (stat(cmd->full_cmd_args[0], &path_stat) != 0)
			file_error(cmd, strerror(errno), 127);
		if (S_ISDIR(path_stat.st_mode))
			file_error(cmd, cmd->full_cmd_args[0], 200);
		else if (S_ISREG(path_stat.st_mode))
			run_file(cmd, envp, exit_status, tmp_fd);
		else
			file_error(cmd, strerror(errno), 127);
	}
	waitpid(pid, &(cmd->exit_status), 0);
}

void	executer(t_command *cmd, char **envp, int *exit_status)
{
	int			tmp_fd;
	t_command	*temp;

	tmp_fd = -1;
	if (!save_stdin(cmd))
		cmd_error(cmd, strerror(errno), errno);
	assign_envp(cmd, envp);
	while (cmd)
	{
		cmd->exit_status = *exit_status;
		if (is_path(cmd->full_cmd_args[0]))
			ex_file(cmd, envp, exit_status, &tmp_fd);
		else
			execute_cmd(cmd, envp, &tmp_fd);
		*exit_status = convert_exit_status(cmd->exit_status);
		expand_exit_status(cmd, *exit_status);
		temp = cmd->next;
		free_cmd(cmd);
		cmd = temp;
	}
}
