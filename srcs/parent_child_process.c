#include "../includes/minishell.h"



void	first_child_process(int *pipe_fd, t_command *cmd, char **envp)
{
	handle_infile(cmd);
	if (cmd->redirection_out_type)
		handle_outfile(cmd);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	run_cmd(cmd->full_cmd_args, envp);
}

void	next_child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp)
{
	if (cmd->redirection_in_type)
		handle_infile(cmd);
	else
		dup2(tmp_fd, STDIN_FILENO);
	if (cmd->redirection_out_type)
		handle_outfile(cmd);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(tmp_fd);
	close(pipe_fd[1]);
	run_cmd(cmd->full_cmd_args, envp);
}

void	parent_process(int tmp_fd, t_command *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->redirection_in_type)
		handle_infile(cmd);
	else
		dup2(tmp_fd, STDIN_FILENO);
	handle_outfile(cmd);
	close(tmp_fd);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	else if (pid == 0)
		run_cmd(cmd->full_cmd_args, envp);
	waitpid(pid, NULL, 0);
}
