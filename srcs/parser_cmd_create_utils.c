#include "../includes/minishell.h"

static t_command	*cmd_last(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_cmd_to_list(t_command **list, t_command *new)
{
	t_command	*last;

	if (!new)
		return ;
	if (!*list)
		*list = new;
	else
	{
		last = cmd_last(*list);
		last->next = new;
	}
}

t_command	*create_new_cmd(t_command **cmd_list, int number_arguments)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (0);
	new_cmd->number_arguments = number_arguments;
	new_cmd->full_cmd_args = malloc(sizeof(char *) * (number_arguments + 1));
	if (!new_cmd->full_cmd_args)
		return(free(new_cmd), NULL);
	new_cmd->full_cmd_args[number_arguments] = NULL;
	new_cmd->next = NULL;
	add_cmd_to_list(cmd_list, new_cmd);
	return (new_cmd);
}
