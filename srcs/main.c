#include "../includes/minishell.h"
#include "../libft/libft.h"

// void	read_tokens(t_token **token_list)
// {
// 	t_token	*token;

// 	token = *token_list;
// 	printf("Token list: \n");
// 	while (token != NULL)
// 	{
// 		printf("'%s'\n", token->content);
// 		token = token->next;
// 	}
// }

// void	read_cmds(t_cmd **cmd_list)
// {
// 	t_cmd		*cmd;
// 	int				i;
// 	int				count;
// 	t_redirection	*redir;

// 	if (!*cmd_list)
// 	{
// 		printf("Command list empty.\n");
// 		return ;
// 	}
// 	cmd = *cmd_list;
// 	count = 1;
// 	printf("Command list: \n");
// 	while (cmd != NULL)
// 	{
// 		printf("-=cmd n°%i=- (%p)\n", count, (void *)cmd);
// 		i = 0;
// 		while (cmd->full_cmd_args && cmd->full_cmd_args[i])
// 		{
// 			printf("'%s'\n", cmd->full_cmd_args[i]);
// 			i++;
// 		}
// 		redir = cmd->redir;
// 		printf("redir is currently %p\n", cmd->redir);
// 		while (redir)
// 		{
// 			printf("	redir: '%s', I/O '%i'\n", redir->name, redir->in_or_out);
// 			redir = redir->next;
// 		}
// 		cmd = cmd->next;
// 		count++;
// 	}
// }

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		i;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	new_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	new_envp[len] = NULL;
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_array(new_envp);
			return (NULL);
		}
		i++;
	}
	return (new_envp);
}

void	process_input(char *input, char ***envp, int *exit_status)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = lexer(input);
	//read_tokens(&token_list);
	free(input);
	if (!pre_parser(token_list))
		return (delete_token_list(&token_list));
	cmd_list = parser(token_list);
	if (cmd_list)
	{
		//read_cmds(&cmd_list);
		expander(cmd_list, *envp);
		expand_exit_status(cmd_list, *exit_status);
		if (!remove_full_quotes(&cmd_list))
			cmd_error(cmd_list, strerror(errno), errno);
		clean_empty_argument(cmd_list);
		executer(cmd_list, envp, exit_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		**new_envp;
	int			exit_status;

	(void)ac;
	(void)av;
	new_envp = copy_envp(envp);
	if (!new_envp)
	{
		print_error(strerror(errno));
		return (1);
	}
	exit_status = 0;
	setup_base_signals();
	input = readline("Minishell$ ");
	while (input)
	{
		add_history(input);
		setup_run_signals();
		g_status = 0;
		process_input(input, &new_envp, &exit_status);
		setup_base_signals();
		if (g_status == 130)
			write(1, "\n", 1);
		if (g_status == 131)
			write(1, "Quit (core dumped)\n", 19);
		input = readline("Minishell$ ");
	}
	free_array(new_envp);
	rl_clear_history();
	return (0);
}
