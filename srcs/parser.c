#include "../includes/minishell.h"

static void	fill_args_in_cmd(t_token *start_token, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->number_arguments)
	{
		cmd->full_cmd_args[i] = start_token->content;
		start_token = start_token->next;
		i++;
	}
}

static void	handle_pipe_next(t_token **current_token, t_command *new_cmd)
{
	while ((*current_token)->content && ((*current_token)->content[0] == '|' || (*current_token)->content[0] == ';'))
	{
		if ((*current_token)->content[0] == '|')
			new_cmd->pipe_next = 1;
		else
			new_cmd->pipe_next = 0;
		free((*current_token)->content);
		(*current_token) = (*current_token)->next;
	}
}

int	build_cmd(t_token **current_token, t_command **cmd_list, t_command **new_cmd)
{
	int	i;

	i = 0;
	while ((*current_token)->content && !((*current_token)->content[0] == '|' 
		|| (*current_token)->content[0] == ';'
		|| (*current_token)->content[0] == '<' || (*current_token)->content[0] == '>'))
	{
		(*current_token) = (*current_token)->next;
		i++;
	}
	if (!((*new_cmd) = create_new_cmd(cmd_list, i)))
		return (0);
	verify_built_in(new_cmd);
	verify_executable(new_cmd);
	verify_pipe_prev(cmd_list, new_cmd);
	return (1);
}

t_command	*parser(t_token *token_list)
{
	t_token		*current_token;
	t_token		*start_token;
	t_command	*new_cmd;
	t_command	*cmd_list;

	cmd_list = NULL;
	current_token = token_list;
	start_token = token_list;
	while (current_token != NULL)
	{
		start_token = current_token;
		if (!build_cmd(&current_token, &cmd_list, &new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		add_cmd_to_list(&cmd_list, new_cmd);
		fill_args_in_cmd(start_token, new_cmd);
		if (!handle_redirections(&current_token, new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		handle_pipe_next(&current_token, new_cmd);
	}
	delete_token_list(&token_list);
	return (cmd_list);
}
