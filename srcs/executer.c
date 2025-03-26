#include "../includes/minishell.h"

static void	cmd_with_pipe(int *tmp_fd, t_command *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		cmd_error(cmd, strerror(errno), errno);
	pid = fork();
	if (pid == -1)
		cmd_error(cmd, strerror(errno), errno);
	if (pid == 0)
		child_process(pipe_fd, tmp_fd, cmd, envp);
	waitpid(pid, &(cmd->exit_status), WNOHANG);
	if (*tmp_fd != -1)
		close(*tmp_fd);
	close(pipe_fd[1]);
	*tmp_fd = pipe_fd[0];
}

static void	cmd_no_pipe(int *tmp_fd, t_command *cmd, char **envp)
{
	pid_t	pid;

	check_input_output(cmd, tmp_fd);
	if (cmd->built_in)
		run_built_in(cmd, envp);
	else
	{
		pid = fork();
		if (pid == -1)
			cmd_error(cmd, strerror(errno), errno);
		else if (pid == 0)
			run_cmd(cmd, envp);
		waitpid(pid, &(cmd->exit_status), 0);
		restore_stdin(cmd);
		*tmp_fd = -1;
	}
}

static void	execute_cmd(t_command *cmd, char **envp, int *tmp_fd)
{
	if (cmd->pipe_next)
		cmd_with_pipe(tmp_fd, cmd, envp);
	else
		cmd_no_pipe (tmp_fd, cmd, envp);
}

static void	execute_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	pid_t	pid;
	struct stat	path_stat;

	pid = fork();
	if (pid == -1)
		file_error(cmd, strerror(errno), errno);
	else if (pid == 0)
	{
		if (stat(cmd->full_cmd_args[0], &path_stat) != 0)
			file_error(cmd, strerror(errno), 127);
		if (S_ISDIR(path_stat.st_mode))
			file_error(cmd, cmd->full_cmd_args[0], 500);
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
	while (cmd)
	{
		cmd->exit_status = *exit_status;
		if (is_path(cmd->full_cmd_args[0]))
			execute_file(cmd, envp, exit_status, &tmp_fd);
		else
			execute_cmd(cmd, envp, &tmp_fd);
		*exit_status = cmd->exit_status;
		expand_exit_status(cmd, *exit_status);
		temp = cmd->next;
		free_cmd(cmd);
		cmd = temp;
		convert_exit_status(exit_status);
	}
}
