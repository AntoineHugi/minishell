#include "../includes/minishell.h"

static void	delete_cmd_redir(t_command *cmd)
{
	t_redirection	*current_redir;

	current_redir = cmd->input;
	free(current_redir->name);
	free(current_redir);
	cmd->input = NULL;
	current_redir = cmd->output;
	free(current_redir->name);
	free(current_redir);
	cmd->output = NULL;
}

static void	delete_cmd_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->full_cmd_args)
	{
		while (i < cmd->number_arguments)
		{
			if (cmd->full_cmd_args[i])
				free(cmd->full_cmd_args[i]);
			i++;
		}
		free(cmd->full_cmd_args);
		cmd->full_cmd_args = NULL;
	}

}

void	delete_cmd_list(t_command **cmd_list)
{
	t_command	*current_cmd;
	t_command	*next_cmd;

	if (!cmd_list || !(*cmd_list))
		return ;
	current_cmd = *cmd_list;
	while (current_cmd)
	{
		next_cmd = current_cmd->next;
		if (current_cmd->input || current_cmd->output)
			delete_cmd_redir(current_cmd);
		if (current_cmd->full_cmd_args)
			delete_cmd_args(current_cmd);
		free(current_cmd);
		current_cmd = next_cmd;
	}
	(*cmd_list) = NULL;
}
