#include "../includes/minishell.h"

void	child_process(int *pipe_fd, int *tmp_fd, t_command *cmd, char **envp)
{
	check_input_output(cmd, tmp_fd);
	if (!cmd->output)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (*tmp_fd != -1)
		close(*tmp_fd);
	close(pipe_fd[1]);
	if (cmd->built_in)
		run_built_in(cmd, envp);
	else
		run_cmd(cmd, envp);
	free_all_cmds(cmd);
	exit(0);
}

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

void	execute_cmd(t_command *cmd, char **envp, int *tmp_fd)
{
	if (cmd->pipe_next)
		cmd_with_pipe(tmp_fd, cmd, envp);
	else
		cmd_no_pipe (tmp_fd, cmd, envp);
}
