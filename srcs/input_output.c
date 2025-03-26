#include "../includes/minishell.h"

void	check_input_output(t_command *cmd, int *tmp_fd)
{
	if (cmd->input)
		handle_infile(cmd);
	else if (*tmp_fd != -1)
	{
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
	}
	if (cmd->output)
		handle_outfile(cmd);
}
