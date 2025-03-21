#include "../includes/minishell.h"

static int	fill_in_redir_in_cmd(t_token **current_token, t_command *cmd)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (0);
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
	cmd->input = redir;
	if ((*current_token)->content[0] == '<' && (*current_token)->content[1] == '<')
		redir->redirection_type = 2;
	else
		redir->redirection_type = 1;
	(*current_token) = (*current_token)->next;
	redir->name = (*current_token)->content;
	return (1);
}

static int	fill_out_redir_in_cmd(t_token **current_token, t_command *cmd)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (0);
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
	cmd->output = redir;
	if ((*current_token)->content[0] == '>' && (*current_token)->content[1] == '>')
		redir->redirection_type = 2;
	else
		redir->redirection_type = 1;
	(*current_token) = (*current_token)->next;
	redir->name = (*current_token)->content;
	return (1);
}

int	handle_redirections(t_token **current_token, t_command *new_cmd)
{
	while ((*current_token) && (*current_token)->content 
		&& ((*current_token)->content[0] == '<' || (*current_token)->content[0] == '>'))
	{
		printf("Current token: %s \n", (*current_token)->content);
		if ((*current_token)->content[0] == '<')
		{
			if (!fill_in_redir_in_cmd(current_token, new_cmd))
				return (0);
		}
		if ((*current_token)->content[0] == '>')
		{
			if (!fill_out_redir_in_cmd(current_token, new_cmd))
				return (0);
		}
		if ((*current_token)->next)
		(*current_token) = (*current_token)->next;
	}
	return (1);
}
