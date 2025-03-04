#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*input2;
	//char	*input3;
	t_command	test;
	t_command	test2;
//	t_command	test3;
	//int i = 0;

	/*input = readline("Minishell$ ");
	while (input)
	{
		//lexer(input);
		free(input);
		input = readline("Minishell$ ");
	}*/
	input = av[ac - 1];
	input = "$TEST hello beans";
	test.infile = "infile";
	test.outfile = NULL;
	test.full_cmd_args = ft_split(input, ' ');
	test.next = &test2;
	test.redirection_in_type = 0;
	test.redirection_out_type = 0;

	input2 = "wc -w";
	test2.infile = "infile";
	test2.outfile = "output";
	test2.full_cmd_args = ft_split(input2, ' ');
	test2.next = NULL;
	test2.redirection_in_type = 0;
	test2.redirection_out_type = 1;
/*
	input3 = "echo hello";
	test3.infile = NULL;
	test3.outfile = NULL;
	test3.full_cmd_args = ft_split(input3, ' ');
	test3.next = NULL;
	test3.redirection_in_type = 0;
	test3.redirection_out_type = 0;
*/
	expander(&test, envp);
	executer(&test, envp);

	/* this part exits, when pressing ctrl-D*/
	/*if (feof(stdin)) {
		free(input);
		exit(0);
		return 0;
	}*/
	/* add ctrl-C function and disable default*/
	/* disable ctrl -\ */
}
