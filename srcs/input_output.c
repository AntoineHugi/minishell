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

int	check_input_output(t_command *cmd, int *tmp_fd)
{
	t_redirection	*start_in;
	t_redirection	*start_out;
	
	start_in = cmd->input;
	start_out = cmd->output;
	if (*tmp_fd != -1)
	{
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
	}
	while (cmd->output)
	{
		if (!handle_outfile(cmd))
			return (0);
		cmd->output = cmd->output->next;
	}
	while (cmd->input)
	{
		if (!handle_infile(cmd))
			return (0);
		cmd->input = cmd->input->next;
	}
	cmd->input = start_in;
	cmd->output = start_out;
	return (1);
}
