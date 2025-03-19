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
		child_process(pipe_fd, *tmp_fd, cmd, envp);
	waitpid(pid, &(cmd->exit_status), 0);
	if (*tmp_fd != -1)
		close(*tmp_fd);
	close(pipe_fd[1]);
	*tmp_fd = pipe_fd[0];
}

static void	cmd_no_pipe(int *tmp_fd, t_command *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->input)
		handle_infile(cmd);
	else if (*tmp_fd != -1)
	{
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
	}
	if (cmd->output)
		handle_outfile(cmd);
	if (cmd->cd && !cmd->pipe_prev)
		change_directory(cmd, envp);
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

static int	multiple_cmd(t_command *cmd, char **envp)
{
	int			tmp_fd;
	int			exit_status;
	t_command	*temp;

	tmp_fd = -1;
	while (cmd->next)
	{
		if (!save_stdin(cmd))
			cmd_error(cmd, strerror(errno), errno);
		if (cmd->pipe_next)
			cmd_with_pipe(&tmp_fd, cmd, envp);
		else
			cmd_no_pipe (&tmp_fd, cmd, envp);
		exit_status = cmd->exit_status;
		temp = cmd->next;
		free_cmd(cmd);
		cmd = temp;
		expand_exit_status(cmd, exit_status);
	}
	parent_process(tmp_fd, cmd, envp);
	return (cmd->exit_status);
}

static int	single_cmd(t_command *cmd, char **envp)
{
	pid_t	pid;

	if (!save_stdin(cmd))
		cmd_error(cmd, strerror(errno), errno);
	if (cmd->input)
		handle_infile(cmd);
	if (cmd->output)
		handle_outfile(cmd);
	if (cmd->cd && !cmd->pipe_prev)
		change_directory(cmd, envp);
	else
	{
		pid = fork();
		if (pid == -1)
			cmd_error(cmd, strerror(errno), errno);
		else if (pid == 0)
			run_cmd(cmd, envp);
		waitpid(pid, &(cmd->exit_status), 0);
	}
	restore_stdin(cmd);
	return (cmd->exit_status);
}

int	executer(t_command *cmd, char **envp, int exit_status)
{
	expand_exit_status(cmd, exit_status);
	if (cmd->next == NULL)
		exit_status = single_cmd(cmd, envp);
	else
		exit_status = multiple_cmd(cmd, envp);
	free_cmd(cmd);
	return (exit_status);
}
