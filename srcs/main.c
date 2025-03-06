#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*input2;
	//char	*input3;
	t_command	test;
	t_command	test2;
	//t_command	test3;
	//int i = 0;

	/*input = readline("Minishell$ ");
	while (input)
	{
		//lexer(input);
		free(input);
		input = readline("Minishell$ ");
	}*/
	
	input = av[ac - 1]; //just to use ac/av


	input = "echo hello";
	test.infile = NULL;
	test.outfile = "output";
	test.full_cmd_args = ft_split(input, ' ');
	test.next = &test2;
	test.redirection_in_type = 0;
	test.redirection_out_type = 2;
	test.limiter = "EOF";

	input2 = "echo bye";
	test2.infile = NULL;
	test2.outfile = "output";
	test2.full_cmd_args = ft_split(input2, ' ');
	test2.next = NULL;
	test2.redirection_in_type = 0;
	test2.redirection_out_type = 2;

	/*input3 = "echo $TEST";
	test3.infile = NULL;
	test3.outfile = "output";
	test3.full_cmd_args = ft_split(input3, ' ');
	test3.next = NULL;
	test3.redirection_in_type = 0;
	test3.redirection_out_type = 1;*/

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
