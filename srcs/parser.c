#include "../includes/minishell.h"

static void	fill_args_in_cmd(t_token *start_token, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->number_arguments)
	{
		cmd->full_cmd_args[i] = start_token->content;
		printf("	Token being filled in: %s \n", start_token->content);
		start_token = start_token->next;
		i++;
	}
}

static void	handle_pipe_next(t_token **current_token, t_command *new_cmd)
{
	printf("	Current token: %s \n", (*current_token)->content);
	if (*current_token && (*current_token)->content && (*current_token)->content[0] == '|')
	{
		new_cmd->pipe_next = 1;
		// free((*current_token)->content);
		// (*current_token)->content = NULL;
	}
}

static void	initialize_cmd_data(t_command **new_cmd)
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
	(*new_cmd)->input = NULL;
	(*new_cmd)->output = NULL;
	(*new_cmd)->errorfile = NULL;
	(*new_cmd)->next = NULL;
}

int	build_cmd(t_token **current_token, t_command **new_cmd)
{
	t_token	*token;
	int	i;

	token = *current_token;
	printf("	Inside build_cmd. \n");
	printf("	Current token: %s \n", (*current_token)->content);
	i = 1;
	while (token && token->content && token->next && token->next->content && 
		!(token->next->content[0] == '|' || token->next->content[0] == ';'
		|| token->next->content[0] == '<' || token->next->content[0] == '>'))
	{
		token = token->next;
		(*current_token) = (*current_token)->next;
		i++;
	}
	if ((*current_token)->next)
		(*current_token) = (*current_token)->next;
	printf("	Creating the cmd... \n");
	if (!((*new_cmd) = create_new_cmd(i)))
		return (0);
	initialize_cmd_data(new_cmd);
	printf("	Cmd created and initialized. \n");
	printf("	Number of arguments : %i \n", (*new_cmd)->number_arguments);
	return (1);
}

t_command	*parser(t_token *token_list)
{
	t_token		*current_token;
	t_token		*start_token;
	t_command	*new_cmd;
	t_command	*cmd_list;

	printf("Parser entered.\n");
	cmd_list = NULL;
	current_token = token_list;
	start_token = token_list;
	while (current_token != NULL)
	{
		start_token = current_token;
		printf("\nBuilding a command...\n");
		if (!build_cmd(&current_token, &new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		printf("Adding the command to the list.\n");
		add_cmd_to_list(&cmd_list, new_cmd);
		printf("Filling in the arguments...\n");
		fill_args_in_cmd(start_token, new_cmd);
		printf("Filling in the redirections...\n");
		if (!handle_redirections(&current_token, new_cmd))
			return (delete_cmd_list(&cmd_list), NULL);
		printf("Adding the pipe information...\n");
		handle_pipe_next(&current_token, new_cmd);
		printf("Pipe information added.\n");
		printf("Current token: %s \n", current_token->content);
		verify_built_in(new_cmd);
		printf("built-ins verified. \n");
		verify_executable(new_cmd);
		printf("Executables verified. \n");
		verify_pipe_prev(&cmd_list, new_cmd);
		printf("Previous pipe verified. \n");
		printf("Current token: %s \n", current_token->content);
		current_token = current_token->next;
	}
	printf("\n");
	read_tokens(&token_list);
	printf("Deleting the unused token contents...\n");
	delete_unused_contents(&token_list);
	printf("Deleting the token list...\n");
	delete_token_list(&token_list);
	printf("Parser ended.\n");
	return (cmd_list);
}
