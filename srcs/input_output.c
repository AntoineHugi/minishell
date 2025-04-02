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
	t_redirection	*redir;

	if (*tmp_fd != -1)
	{
		dup2(*tmp_fd, STDIN_FILENO);
		close(*tmp_fd);
	}
	redir = cmd->redir;
	while (redir)
	{
		if (redir->in_or_out == 0)
		{
			if (!handle_infile(cmd, redir))
				return (0);
		}
		else
		{
			if (!handle_outfile(redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
