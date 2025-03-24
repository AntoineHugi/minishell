#include "../includes/minishell.h"

static void	delete_cmd_redir(t_command *cmd)
{
	if (cmd->input)
	{
		if (cmd->input->name)
		{
			free(cmd->input->name);
			cmd->input->name = NULL;
		}
		free(cmd->input);
		cmd->input = NULL;
	}
	if (cmd->output)
	{
		if (cmd->output->name)
		{
			free(cmd->output->name);
			cmd->output->name = NULL;
		}
		free(cmd->output);
		cmd->output = NULL;
	}
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
