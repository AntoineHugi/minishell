#include "../includes/minishell.h"

static void	single_cmd(t_command *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->input)
		handle_infile(cmd);
	if (cmd->output)
		handle_outfile(cmd);
	pid = fork();
	if (pid == -1)
		cmd_error(cmd, strerror(errno), errno);
	else if (pid == 0)
		run_cmd(cmd, envp);
	waitpid(pid, &(cmd->exit_status), 0);
	restore_stdin(cmd);
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

int	executer(t_command *cmd, char **envp, int exit_status)
{
	int	tmp_fd; 

	if (!save_stdin(cmd))
		cmd_error(cmd, strerror(errno), errno);
	tmp_fd = -1;
	expand_exit_status(cmd, exit_status);
	if (cmd->next == NULL)
		single_cmd(cmd, envp);
	else
	{
		while (cmd->next)
		{
			if (cmd->pipe_next)
				cmd_with_pipe(&tmp_fd, cmd, envp);
			else
				cmd_no_pipe (&tmp_fd, cmd, envp);
			exit_status = cmd->exit_status;
			cmd = cmd->next;
			expand_exit_status(cmd, exit_status);
		}
		parent_process(tmp_fd, cmd, envp);
	}
	return (exit_status);
}
