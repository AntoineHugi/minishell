#include "../includes/minishell.h"

static int	has_output(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->in_or_out == 1)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static void	child_process(int *pipe_fd, int *tmp_fd, t_cmd *cmd, char **envp)
{
	if (!check_input_output(cmd, tmp_fd))
	{
		restore_stdin(cmd);
		free_all_cmds(cmd);
		rl_clear_history();
		exit(1);
	}
	if (!has_output(cmd))
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (*tmp_fd != -1)
		close(*tmp_fd);
	close(pipe_fd[1]);
	if (cmd->built_in)
		run_built_in(cmd, envp, *tmp_fd);
	else
		run_cmd(cmd, envp, *tmp_fd);
	free_all_cmds(cmd);
	rl_clear_history();
	exit(0);
}

static void	cmd_with_pipe(int *tmp_fd, t_cmd *cmd, char **envp)
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

static void	cmd_no_pipe(int *tmp_fd, t_cmd *cmd, char **envp)
{
	pid_t	pid;

	if (!check_input_output(cmd, tmp_fd))
	{
		cmd->exit_status = 1;
		return ;
	}
	if (cmd->built_in)
		run_built_in(cmd, envp, *tmp_fd);
	else
	{
		pid = fork();
		if (pid == -1)
			cmd_error(cmd, strerror(errno), errno);
		else if (pid == 0)
			run_cmd(cmd, envp, *tmp_fd);
		waitpid(pid, &(cmd->exit_status), 0);
	}
	*tmp_fd = -1;
}

void	execute_cmd(t_cmd *cmd, char **envp, int *tmp_fd)
{
	if (cmd->pipe_next)
		cmd_with_pipe(tmp_fd, cmd, envp);
	else
		cmd_no_pipe (tmp_fd, cmd, envp);
}
