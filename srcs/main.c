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

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		**new_envp;
	int			exit_status;
	t_token		*token_list;
	t_command	*cmd_list;

    new_envp = copy_envp(envp);
	if (!new_envp)
		print_error(strerror(errno), errno);
	exit_status = 0;
	input = readline("Minishell$ ");
	while (input)
 	{
		token_list = lexer(input);
		//add_history(input);
 		free(input);
 		cmd_list = parser(token_list);
		expander(cmd_list, new_envp);
		exit_status = executer(cmd_list, new_envp, exit_status);
		input = readline("Minishell$ ");
 	}
	printf("\n%s%i\n",av[0],ac);
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
