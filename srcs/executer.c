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
		waitpid(pid, &(cmd->exit_status), WNOHANG);
		restore_stdin(cmd);
		*tmp_fd = -1;
	}
}

static void	execute_cmd(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	t_command	*temp;

	while (cmd->next)
	{
		if (cmd->pipe_next)
			cmd_with_pipe(tmp_fd, cmd, envp);
		else
			cmd_no_pipe (tmp_fd, cmd, envp);
		*exit_status = cmd->exit_status;
		temp = cmd->next;
		free_cmd(cmd);
		cmd = temp;
		expand_exit_status(cmd, *exit_status);
		cmd->exit_status = *exit_status;
	}
	parent_process(tmp_fd, cmd, envp);
	restore_stdin(cmd);
	*exit_status = cmd->exit_status;
	convert_exit_status(exit_status);
	free_cmd(cmd);
}
/*
static void	execute_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		cmd_error(cmd, strerror(errno), errno);
	else if (pid == 0)
	{
		if (access(cmd->full_cmd_args[0], F_OK) == 0)
		{
			if (access(cmd->full_cmd_args[0], X_OK) == 0
				&& access(cmd->full_cmd_args[0], R_OK == 0))
				run_file(cmd, envp, exit_status, tmp_fd);
			else
				cmd_error(cmd, strerror(errno), errno);
		}
		else
			cmd_error(cmd, strerror(errno), 127);
	}
	waitpid(pid, &(cmd->exit_status), 0);
}*/

void	executer(t_command *cmd, char **envp, int *exit_status)
{
	int	tmp_fd;
	
	tmp_fd = -1;
	cmd->exit_status = *exit_status;
	if (!save_stdin(cmd))
		cmd_error(cmd, strerror(errno), errno);
	/*if (is_path(cmd->full_cmd_args[0]))
		execute_file(cmd, envp, exit_status, &tmp_fd);
	else*/
	execute_cmd(cmd, envp, exit_status, &tmp_fd);
}
