#include "../includes/minishell.h"

void	restore_stdin(t_command *cmd)
{
	dup2(cmd->og_stdin, STDIN_FILENO);
	dup2(cmd->og_stdout, STDOUT_FILENO);
}

int	save_stdin(t_command *cmd)
{
	while (cmd)
	{
		cmd->og_stdin = dup(STDIN_FILENO);
		if (cmd->og_stdin == -1)
			return (0);
		cmd->og_stdout = dup(STDOUT_FILENO);
		if (cmd->og_stdout == -1)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

void	check_input_output(t_command *cmd, int *tmp_fd)
{
	if (cmd->input)
		handle_infile(cmd);
	else if (*tmp_fd != -1)
	{
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
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
