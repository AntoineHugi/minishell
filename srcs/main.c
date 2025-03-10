#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*input2;
	//char	*input3;
	t_command	cmd1;
	t_command	cmd2;
	//t_command	test3;
	t_redirection infile1;
	t_redirection infile2;
	t_redirection outfile1;
	t_redirection outfile2;

	/*input = readline("Minishell$ ");
	while (input)
	{
		//lexer(input);
		free(input);
		input = readline("Minishell$ ");
	}*/
	
	input = av[ac - 1]; //just to use ac/av

	infile1.name = "infile1";
	infile1.redirection_type = 1;
	infile2.name = "infile2";
	infile2.redirection_type = 2;

	outfile1.name = "output1";
	outfile1.redirection_type = 1;
	outfile2.name = "output2";
	outfile2.redirection_type = 2;

	input = "echo hello";
	cmd1.input = &infile1;
	cmd1.output = NULL;
	cmd1.full_cmd_args = ft_split(input, ' ');
	cmd1.next = &cmd2;
	cmd1.limiter = "EOF";

	input2 = "wc -l";
	cmd2.input = NULL;
	cmd2.output = &outfile2;
	cmd2.full_cmd_args = ft_split(input2, ' ');
	cmd2.next = NULL;

	/*input3 = "echo $TEST";
	test3.infile = NULL;
	test3.outfile = "output";
	test3.full_cmd_args = ft_split(input3, ' ');
	test3.next = NULL;
	test3.redirection_in_type = 0;
	test3.redirection_out_type = 1;*/

	expander(&cmd1, envp);
	executer(&cmd1, envp);
	free_array(cmd1.full_cmd_args);
	free_array(cmd2.full_cmd_args);
	//free_array(test3.full_cmd_args);

	/* this part exits, when pressing ctrl-D*/
	/*if (feof(stdin)) {
		free(input);
		exit(0);
		return 0;
	}*/
	/* add ctrl-C function and disable default*/
	/* disable ctrl -\ */
}
