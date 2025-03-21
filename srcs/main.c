#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

void	read_tokens(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token != NULL)
	{
		printf("'%s'\n", token->content);
		token = token->next;
	}
}

void	read_cmds(t_command **cmd_list)
{
	t_command	*cmd;
	int			i;
	int			count;

	if (!*cmd_list)
	{
		printf("Command list empty.\n");
		return ;
	}
	cmd = *cmd_list;
	count = 1;
	while (cmd != NULL)
	{
		printf("-=cmd n°%i=- (%p)\n", count, (void *)cmd);
		i = 0;
		while (cmd->full_cmd_args && cmd->full_cmd_args[i])
		{
			printf("'%s'\n", cmd->full_cmd_args[i]);
			i++;
		}
		if (cmd->input)
			printf("	Input redir: '%s'\n", cmd->input->name);
		if (cmd->output)
			printf("	Output redir: '%s'\n", cmd->output->name);
		cmd = cmd->next;
		count++;
	}
}

int	main(int ac, char **av, char **envp)
{
	// char		*input;
	// char		input[] = "pwd; cd /usr/bin; pwd";
	// char		input[] = "env | grep USER";
	char		input[] = "grep something < file.txt | sort | uniq";
	// char		input[] = "ls -R /usr/bin | head -n 10";
	// char		input[] = "echo 'first' | tee output.txt | cat -n";
	// char		input[] = "unset PATH; echo $PATH";
	// char		input[] = "diff file1.txt file2.txt | less";
	// char		input[] = "echo 'Hello, world!' > file.txt";
	// char		input[] = "echo 'Appending text' >> file1.txt > file2.txt";
	// char		input[] = "cat < input.txt | wc -l";
	// char		input[] = "cat < input.txt > output.txt";
	// char		input[] = "cat << EOF > example.txt";
	// char		input[] = "cat << EOF > example.txt 'Multi-line text here' EOF";
	t_token		*token_list;
	t_command	*cmd_list;
	int i = 0;

	// input = readline("Minishell$ ");
	printf("Turning singular string into tokens... ");
	token_list = lexer(input);
	// free(input);
	printf("Reading tokens: \n");
	read_tokens(&token_list);
	printf("Entering Parser... ");
	cmd_list = parser(token_list);
	printf("Reading commands : \n");
	read_cmds(&cmd_list);
	printf("\nFinished!\n");
	return (0);
}

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


// int	main(int ac, char **av, char **envp)
// {
// 	char	*input;
// 	t_command	test;
// 	int i = 0;

// 	/*input = readline("Minishell$ ");
// 	while (input)
// 	{
// 		//lexer(input);
// 		free(input);
// 		input = readline("Minishell$ ");
// 	}*/
// 	input = av[ac - 1];
// 	input = "$TEST hello";
// 	test.infile = "infile";
// 	test.outfile = "output";
// 	test.full_cmd_args = ft_split(input, ' ');
// 	test.next = NULL;
// 	while (test.full_cmd_args[i])
// 	{
// 		printf("%s\n", test.full_cmd_args[i]);
// 		i++;
// 	}
// 	i = 0;
// 	expander(&test, envp);
// 	while (test.full_cmd_args[i])
// 	{
// 		printf("%s\n", test.full_cmd_args[i]);
// 		free(test.full_cmd_args[i]);
// 		i++;
// 	}
// 	free(test.full_cmd_args);

	

	/* this part exits, when pressing ctrl-D*/
	/*if (feof(stdin)) {
		free(input);
		exit(0);
		return 0;
	}*/
	/* add ctrl-C function and disable default*/
	/* disable ctrl -\ */
// }
