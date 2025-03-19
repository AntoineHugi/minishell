#include "../includes/minishell.h"

static void	generate_input(char *limiter, int fd)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (buff_check(limiter, buffer))
			write(fd, buffer, ft_strlen(buffer));
		else
		{
			free(buffer);
			break ;
		}
		free (buffer);
	}
}

static int	here_doc_fd(char *limiter)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		print_error("piping failed", EXIT_FAILURE);
	generate_input(limiter, fd_here_doc[1]);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

void	b_first_child_process(int *pipe_fd, char **argv, char **envp, int hd)
{
	int		fd_infile;

	if (hd == 1)
	{
		fd_infile = here_doc_fd (argv[2]);
		dup2(fd_infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(fd_infile);
		close(pipe_fd[1]);
		run_cmd(argv[3], envp);
	}
	else
	{
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile == -1)
			print_error(argv[1], ENOENT);
		dup2(fd_infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(fd_infile);
		close(pipe_fd[1]);
		run_cmd(argv[2], envp);
	}
}

void	b_next_child_process(int *pipe_fd, int tmp_fd, char *cmd, char **envp)
{
	dup2(tmp_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(tmp_fd);
	close(pipe_fd[1]);
	run_cmd(cmd, envp);
}

void	b_parent_process(int tmp_fd, int ac, char **av, char **envp)
{
	int	fd_out;
	int	hd;

	hd = check_heredoc(av[1]);
	if (hd == 0)
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
		print_error(av[ac - 1], ENOENT);
	dup2(tmp_fd, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(tmp_fd);
	run_cmd(av[ac - 2], envp);
	print_error("execve failed", EXIT_FAILURE);
}
