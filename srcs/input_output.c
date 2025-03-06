#include "../includes/minishell.h"

static int	buff_check(char *limiter, char *buffer)
{
	if (!buffer)
		return (0);
	if (!ft_strlen(buffer))
		return (1);
	if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)))
		return (0);
	return (1);
}

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

int	here_doc_fd(char *limiter)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		print_error("piping failed", EXIT_FAILURE);
	generate_input(limiter, fd_here_doc[1]);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

/* need to deal with extra input files (appending) */
void	handle_infile(t_command *cmd)
{
	int	fd_infile;

	if (cmd->redirection_in_type == 1)
	{
		fd_infile = open(cmd->infile, O_RDONLY);
		if (fd_infile == -1)
			print_error(strerror(errno), errno);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (cmd->redirection_in_type == 2)
	{
		fd_infile = here_doc_fd(cmd->limiter);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
}

void	handle_outfile(t_command *cmd)
{
	int	fd_outfile;

	if (cmd->redirection_out_type == 1)
	{
		fd_outfile = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	if (cmd->redirection_out_type == 2)
	{
		fd_outfile = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}
