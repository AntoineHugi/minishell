#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*input2;
	char	*input3;
	t_command	cmd1;
	t_command	cmd2;
	t_command	cmd3;
	//t_redirection infile1;
	//t_redirection infile2;
	t_redirection outfile1;
	//t_redirection outfile2;

	/*input = readline("Minishell$ ");
	while (input)
	{
		//lexer(input);
		free(input);
		input = readline("Minishell$ ");
	}*/
	
	input = av[ac - 1]; //just to use ac/av

	//infile1.name = "infile1";
	//infile1.redirection_type = 1;
	//infile2.name = "infile2";
	//infile2.redirection_type = 1;

	outfile1.name = "output1";
	outfile1.redirection_type = 1;
	//outfile2.name = "output2";
	//outfile2.redirection_type = 1;

	input = "echo hello";
	cmd1.input = NULL;
	cmd1.output = NULL;
	cmd1.full_cmd_args = ft_split(input, ' ');
	cmd1.pipe_next = 0;
	cmd1.next = &cmd2;
	cmd1.limiter = "EOF";

	input2 = "pwd";
	cmd2.input = NULL;
	cmd2.output = &outfile1;
	cmd2.pipe_next = 0;
	cmd2.full_cmd_args = ft_split(input2, ' ');
	cmd2.next = &cmd3;

	input3 = "echo hi";
	cmd3.input = NULL;
	cmd3.output = NULL;
	cmd3.full_cmd_args = ft_split(input3, ' ');
	cmd3.next = NULL;

	/*int i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
	*/

	


	expander(&cmd1, envp);
	executer(&cmd1, envp);
	free_array(cmd1.full_cmd_args);
	free_array(cmd2.full_cmd_args);
	free_array(cmd3.full_cmd_args);

	/* this part exits, when pressing ctrl-D*/
	/*if (feof(stdin)) {
		free(input);
		exit(0);
		return 0;
	}*/
	/* add ctrl-C function and disable default*/
	/* disable ctrl -\ */
}
