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

static void	generate_input(t_command *cmd, char *limiter, int fd)
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

int	here_doc_fd(t_command *cmd, char *limiter)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		cmd_error(cmd, strerror(errno), errno);
	generate_input(cmd, limiter, fd_here_doc[1]);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

void	handle_infile(t_command *cmd)
{
	int	fd_infile;

	if (cmd->input->redirection_type == 1)
	{
		fd_infile = open(cmd->input->name, O_RDONLY);
		if (fd_infile == -1)
			cmd_error(cmd, strerror(errno), errno);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (cmd->input->redirection_type == 2)
	{
		fd_infile = here_doc_fd(cmd, cmd->input->name);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
}

void	handle_outfile(t_command *cmd)
{
	int	fd_out;

	if (cmd->output->redirection_type == 1)
	{
		fd_out = open(cmd->output->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd_out == -1)
			cmd_error(cmd, strerror(errno), errno);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (cmd->output->redirection_type == 2)
	{
		fd_out = open(cmd->output->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd_out == -1)
			cmd_error(cmd, strerror(errno), errno);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
