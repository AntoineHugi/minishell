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

static void	generate_input(t_cmd *cmd, char *limiter, int fd)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			cmd_error(cmd, strerror(errno), errno);
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

static int	here_doc_fd(t_cmd *cmd, char *limiter)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		cmd_error(cmd, strerror(errno), errno);
	generate_input(cmd, limiter, fd_here_doc[1]);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

int	handle_infile(t_cmd *cmd, t_redirection *redir)
{
	int	fd_infile;

	if (redir->redirection_type == 1)
	{
		fd_infile = open(redir->name, O_RDONLY);
		if (fd_infile == -1)
		{
			print_error(strerror(errno));
			return (0);
		}
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (redir->redirection_type == 2)
	{
		fd_infile = here_doc_fd(cmd, redir->name);
		if (fd_infile)
		{
			dup2(fd_infile, STDIN_FILENO);
			close(fd_infile);
		}
		else
			return (0);
	}
	return (1);
}
