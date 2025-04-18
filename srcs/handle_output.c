#include "../includes/minishell.h"

int	handle_outfile(t_redirection *redir)
{
	int	fd_out;

	if (redir->redirection_type == 1)
	{
		fd_out = open(redir->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd_out == -1)
		{
			print_error(strerror(errno));
			return (0);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (redir->redirection_type == 2)
	{
		fd_out = open(redir->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd_out == -1)
		{
			print_error(strerror(errno));
			return (0);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (1);
}
