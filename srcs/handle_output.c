#include "../includes/minishell.h"

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
