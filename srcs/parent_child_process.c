#include "../includes/minishell.h"

void	first_child_process(int *pipe_fd, t_command *cmd, char **envp)
{
	int		fd_infile;

	if (cmd->redirection_in_type == 2)
	{
		//fd_infile = here_doc_fd (argv[2]);
		//dup2(fd_infile, STDIN_FILENO);
		//close(fd_infile);
	}
	else if (cmd->redirection_in_type == 1)
	{
		fd_infile = open(cmd->infile, O_RDONLY);
		if (fd_infile == -1)
			print_error(strerror(errno), errno);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	run_cmd(cmd->full_cmd_args, envp);
}

void	next_child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp)
{
	dup2(tmp_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(tmp_fd);
	close(pipe_fd[1]);
	run_cmd(cmd->full_cmd_args, envp);
}

void	parent_process(int tmp_fd, t_command *cmd, char **envp)
{
	int	fd_out;
	pid_t	pid;

	if (cmd->redirection_out_type == 0)
		fd_out = 0;
	if (cmd->redirection_out_type == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmd->redirection_out_type == 2)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
		print_error(strerror(errno), errno);
	dup2(tmp_fd, STDIN_FILENO);
	if (fd_out)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	close(tmp_fd);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	else if (pid == 0)
		run_cmd(cmd->full_cmd_args, envp);
	waitpid(pid, NULL, 0);	
}
