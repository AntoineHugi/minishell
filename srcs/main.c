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

int	main(int arc, char **arv)
{
	t_token *token_list;
	char	*string;
	
	(void)arc;
	printf("Entering program... \n");
	printf("Building singular string... \n");
	if (arc > 2)
		string = ft_strjoin_all(arv, ' ');
	else
		string = arv[1];
	printf("Full joined cmd: %s \n", string);
	printf("Turning singular string into tokens... \n");
	token_list = lexer(string);
	printf("Reading tokens... \n");
	read_tokens(&token_list);
	return (0);
}


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
