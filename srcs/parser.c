#include "../includes/minishell.h"

static void	fill_args_in_cmd(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->number_arguments)
	{
		if (token->content[0] == '<' || token->content[0] == '>')
			token = token->next->next;
		else
		{
			cmd->full_cmd_args[i] = token->content;
			token = token->next;
			i++;
		}
	}
}

static void	handle_pipe_next(t_token **current_token, t_cmd *new_cmd)
{
	if (*current_token && (*current_token)->content
		&& (*current_token)->content[0] == '|')
		new_cmd->pipe_next = 1;
	if ((*current_token) && (*current_token)->next)
		(*current_token) = (*current_token)->next;
}

static void	initialize_cmd_data(t_cmd **new_cmd)
{
	(*new_cmd)->pipe_next = 0;
	(*new_cmd)->pipe_prev = 0;
	(*new_cmd)->og_stdin = 0;
	(*new_cmd)->og_stdout = 0;
	(*new_cmd)->built_in = 0;
	(*new_cmd)->cd = 0;
	(*new_cmd)->exit_status = 0;
	(*new_cmd)->executable = 0;
	(*new_cmd)->cmd_path = NULL;
	(*new_cmd)->redir = NULL;
	(*new_cmd)->errorfile = NULL;
	(*new_cmd)->next = NULL;
}

int	build_cmd(t_token **token, t_cmd **new_cmd)
{
	int		count;

	count = 0;
	while (*token && (*token)->content && !((*token)->content[0] == '|'
			|| (*token)->content[0] == ';'))
	{
		if ((*token)->content[0] == '<' || (*token)->content[0] == '>')
			(*token) = (*token)->next->next;
		else
		{
			(*token) = (*token)->next;
			count++;
		}
	}
	if (!((*new_cmd) = create_new_cmd(count)))
		return (0);
	initialize_cmd_data(new_cmd);
	return (1);
}

t_cmd	*parser(t_token *token_list)
{
	t_token	*current_token;
	t_token	*start_token;
	t_cmd	*new_cmd;
	t_cmd	*cmd_list;

	cmd_list = NULL;
	current_token = token_list;
	start_token = token_list;
	while (current_token != NULL)
	{
		start_token = current_token;
		if (!build_cmd(&current_token, &new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		add_cmd_to_list(&cmd_list, new_cmd);
		fill_args_in_cmd(start_token, new_cmd);
		if (!handle_redirections(&start_token, new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		handle_pipe_next(&current_token, new_cmd);
		verify_cmd_specs(&cmd_list, new_cmd);
	}
	delete_unused_contents(&token_list);
	delete_token_list(&token_list);
	return (cmd_list);
}
