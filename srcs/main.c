#include "../includes/minishell.h"
#include "../libft/libft.h"

void	read_tokens(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	printf("Token list: \n");
	while (token != NULL)
	{
		printf("'%s'\n", token->content);
		token = token->next;
	}
}

void	read_cmds(t_command **cmd_list)
{
	t_command		*cmd;
	int				i;
	int				count;
	t_redirection	*redir;

	if (!*cmd_list)
	{
		printf("Command list empty.\n");
		return ;
	}
	cmd = *cmd_list;
	count = 1;
	printf("Command list: \n");
	while (cmd != NULL)
	{
		printf("-=cmd n°%i=- (%p)\n", count, (void *)cmd);
		i = 0;
		while (cmd->full_cmd_args && cmd->full_cmd_args[i])
		{
			printf("'%s'\n", cmd->full_cmd_args[i]);
			i++;
		}
		redir = cmd->redir;
		printf("redir is currently %p\n", cmd->redir);
		while (redir)
		{
			printf("	redir: '%s', I/O '%i'\n", redir->name, redir->in_or_out);
			redir = redir->next;
		}
		cmd = cmd->next;
		count++;
	}
}

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

void	process_input(char *input, char **envp, int *exit_status)
{
	t_token		*token_list;
	t_command	*cmd_list;
	
	token_list = lexer(input);
	read_tokens(&token_list);
 	free(input);
 	cmd_list = parser(token_list);
	if (cmd_list)
	{
		read_cmds(&cmd_list);
		//printf("redir is currently %p\n", cmd_list->redir);
		expander(cmd_list, envp);
		//printf("redir is currently %p\n", cmd_list->redir);
		expand_exit_status(cmd_list, *exit_status);
		//printf("redir is currently %p\n", cmd_list->redir);
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

	setup_signals();
	new_envp = copy_envp(envp);
	if (!new_envp)
	{
		print_error(strerror(errno));
		return (1);
	}
	exit_status = 0;
	input = readline("Minishell$ ");
	while (input)
 	{
		add_history(input);
		process_input(input, new_envp, &exit_status);
		input = readline("Minishell$ ");
 	}
	if (ac > 1)
		printf("\n%s%i\n",av[0],ac); //just to use ac av
	free_array(new_envp);
	rl_clear_history();
	return (0);
}

	/* this part exits, when pressing ctrl-D*/
	/*if (feof(stdin)) {
		free(input);
		exit(0);
		return 0;
	}*/
	/* add ctrl-C function and disable default*/
	/* disable ctrl -\ */

// int	main(int ac, char **av, char **envp)
// {
// 	// char		*input;
// 	// char		input[] = "pwd; cd /usr/bin; pwd";
// 	// char		input[] = "env | grep USER";
// 	// char		input[] = "grep something < file.txt | sort | uniq";
// 	// char		input[] = "ls -R /usr/bin | head -n 10";
// 	char		input[] = "echo 'first' | tee output.txt | cat -n";
// 	// char		input[] = "unset PATH; echo $PATH";
// 	// char		input[] = "diff file1.txt file2.txt | less";
// 	// char		input[] = "echo 'Hello, world!' > file.txt";
// 	// char		input[] = "echo 'Appending text' >> file1.txt > file2.txt";
// 	// char		input[] = "cat < input.txt | wc -l";
// 	// char		input[] = "cat < input.txt > output.txt";
// 	// char		input[] = "cat << EOF > example.txt";
// 	// char		input[] = "cat << EOF > example.txt 'Multi-line text here' EOF";
// 	t_token		*token_list;
// 	t_command	*cmd_list;
// 	int i = 0;

// 	// input = readline("Minishell$ ");
// 	printf("Turning singular string into tokens... ");
// 	token_list = lexer(input);
// 	// free(input);
// 	printf("Reading tokens: \n");
// 	read_tokens(&token_list);
// 	cmd_list = parser(token_list);
// 	printf("Reading commands : \n");
// 	read_cmds(&cmd_list);
// 	printf("\nFinished!\n");
// 	return (0);
// }

// int	main(int arc, char **arv)
// {
// 	t_token *token_list;
// 	char	*string;
	
// 	(void)arc;
// 	printf("Entering program... \n");
// 	printf("Building singular string... \n");
// 	if (arc > 2)
// 		string = ft_strjoin_all(arv, ' ');
// 	else
// 		string = arv[1];
// 	printf("Full joined cmd: %s \n", string);
// 	printf("Turning singular string into tokens... \n");
// 	token_list = lexer(string);
// 	printf("Reading tokens... \n");
// 	read_tokens(&token_list);
// 	return (0);
// }




// }
