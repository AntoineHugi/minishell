#include "../includes/minishell.h"

static int	fill_in_redir_in_cmd(t_token **current_token, t_cmd *cmd)
{
	t_redirection	*last_redir;
	t_redirection	*new_redir;

	new_redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redir)
		return (0);
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		last_redir = cmd->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	new_redir->in_or_out = 0;
	if ((*current_token)->content[0] == '<'
		&& (*current_token)->content[1] == '<')
		new_redir->redirection_type = 2;
	else
		new_redir->redirection_type = 1;
	(*current_token) = (*current_token)->next;
	new_redir->name = (*current_token)->content;
	new_redir->next = NULL;
	return (1);
}

static int	fill_out_redir_in_cmd(t_token **current_token, t_cmd *cmd)
{
	t_redirection	*last_redir;
	t_redirection	*new_redir;

	new_redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redir)
		return (0);
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		last_redir = cmd->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	new_redir->in_or_out = 1;
	if ((*current_token)->content[0] == '>'
		&& (*current_token)->content[1] == '>')
		new_redir->redirection_type = 2;
	else
		new_redir->redirection_type = 1;
	(*current_token) = (*current_token)->next;
	new_redir->name = (*current_token)->content;
	new_redir->next = NULL;
	return (1);
}

int	handle_redirections(t_token **token, t_cmd *new_cmd)
{
	while ((*token) && (*token)->content
		&& !((*token)->content[0] == ';'
			|| (*token)->content[0] == '|'))
	{
		if ((*token)->content[0] == '<')
		{
			if (!fill_in_redir_in_cmd(token, new_cmd))
				return (0);
		}
		if ((*token)->content[0] == '>')
		{
			if (!fill_out_redir_in_cmd(token, new_cmd))
				return (0);
		}
		(*token) = (*token)->next;
	}
	return (1);
}
