#include "../includes/minishell.h"

static void	single_cmd(int tmp_fd, t_command *cmd, char **envp)
{
	pid_t	pid;
	
	if (cmd->input)
		handle_infile(cmd);
	else if (tmp_fd != -1)
		dup2(tmp_fd, STDIN_FILENO);
	if (cmd->output)
		handle_outfile(cmd);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	else if (pid == 0)
		run_cmd(cmd, envp);
	waitpid(pid, NULL, 0);
}


static int	create_pipe(int tmp_fd, t_command *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		print_error(strerror(errno), errno);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	if (pid == 0)
		child_process(pipe_fd, tmp_fd, cmd, envp);
	waitpid(pid, NULL, 0);
	if (tmp_fd != -1)
		close(tmp_fd);
	close(pipe_fd[1]);
	tmp_fd = pipe_fd[0];
	return (tmp_fd);
}

static void	restore_fd(int *tmp_fd, int save_stdin)
{
	close(*tmp_fd);
	*tmp_fd = -1;
	dup2(save_stdin, STDIN_FILENO);
}

int	executer(t_command *cmd, char **envp)
{
	int	tmp_fd;
	int save_stdin;

	save_stdin = dup(STDIN_FILENO);
	tmp_fd = -1;
	if (cmd->next == NULL)
		single_cmd(tmp_fd, cmd, envp);
	else
	{
		while (cmd->next != NULL)
		{
			if (cmd->pipe_next)
				tmp_fd = create_pipe(tmp_fd, cmd, envp);
			else
			{
				single_cmd(tmp_fd, cmd, envp);
				restore_fd(&tmp_fd, save_stdin);
			}
			cmd = cmd->next;
		}
		parent_process(tmp_fd, cmd, envp);
	}
	close(save_stdin);
	return (0);
}
