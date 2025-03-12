#include "../includes/minishell.h"

void	own_exit(t_command *cmd)
{
	if (cmd->pipe_next || cmd->pipe_prev)
		return ;
	else
		exit(0);
		//exit_program(cmd); // make sure to clean up and free
}