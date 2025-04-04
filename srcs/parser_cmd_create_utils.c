#include "../includes/minishell.h"

static t_cmd	*cmd_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_cmd_to_list(t_cmd **list, t_cmd *new)
{
	t_cmd	*last;

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

t_cmd	*create_new_cmd(int number_arguments)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (0);
	new_cmd->number_arguments = number_arguments;
	new_cmd->full_cmd_args = malloc(sizeof(char *) * (number_arguments + 1));
	if (!new_cmd->full_cmd_args)
		return (free(new_cmd), NULL);
	new_cmd->full_cmd_args[number_arguments] = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
