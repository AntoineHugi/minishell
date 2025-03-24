#include "../includes/minishell.h"

void	child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp)
{
	if (cmd->input)
		handle_infile(cmd);
	else if (tmp_fd != -1)
		dup2(tmp_fd, STDIN_FILENO);
	if (cmd->output)
		handle_outfile(cmd);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (tmp_fd != -1)
		close(tmp_fd);
	close(pipe_fd[1]);
	if (!cmd->built_in)
		run_built_in(cmd, envp);
	else
		run_cmd(cmd, envp);
	free_all_cmds(cmd);
	exit(0);
}

void	parent_process(int tmp_fd, t_command *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->input)
		handle_infile(cmd);
	else if (tmp_fd != -1)
	{
		dup2(tmp_fd, STDIN_FILENO);
		close(tmp_fd);
	}
	if (cmd->output)
		handle_outfile(cmd);
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
	}
}
