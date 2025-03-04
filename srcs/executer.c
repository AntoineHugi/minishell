#include "../includes/minishell.h"

/*void	single_cmd(t_command *cmd, char **envp)
{

}*/

static int	middle_pipe(int tmp_fd, t_command *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		print_error(strerror(errno), errno);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	if (pid == 0)
		next_child_process(pipe_fd, tmp_fd, cmd, envp);
	waitpid(pid, NULL, 0);
	close(tmp_fd);
	close(pipe_fd[1]);
	tmp_fd = pipe_fd[0];
	return (tmp_fd);
}

static int	first_pipe(t_command *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		print_error(strerror(errno), errno);
	pid = fork();
	if (pid == -1)
		print_error(strerror(errno), errno);
	else if (pid == 0)
		first_child_process(pipe_fd, cmd, envp);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

int	executer(t_command *cmd, char **envp)
{
	int	tmp_fd;
	int	is_first;

	is_first = 1;
	tmp_fd = -1;
	if (cmd->next == NULL){}
		//single_cmd(cmd, envp);
	else
	{
		while (cmd->next != NULL)
		{
			if (is_first)
			{
				tmp_fd = first_pipe(cmd, envp);
				is_first = 0;
			}
			else
				tmp_fd = middle_pipe(tmp_fd, cmd, envp);
			cmd = cmd->next;
		}
		parent_process(tmp_fd, cmd, envp);
	}
	return (0);
}
