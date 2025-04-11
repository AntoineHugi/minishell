#include "../includes/minishell.h"
#include "../libft/libft.h"

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

	setup_run_signals();
	g_status = 0;
	token_list = lexer(input);
	free(input);
	if (!pre_parser(token_list))
	{
		*exit_status = 2;
		return (delete_token_list(&token_list));
	}
	cmd_list = parser(token_list);
	if (cmd_list)
	{
		expander(cmd_list, *envp);
		expand_exit_status(cmd_list, *exit_status);
		if (!remove_full_quotes(&cmd_list))
			cmd_error(cmd_list, strerror(errno), errno);
		clean_empty_argument(cmd_list);
		executer(cmd_list, envp, exit_status);
	}
	setup_base_signals();
	sig_msg(exit_status);
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
		return (print_error(strerror(errno)), 1);
	exit_status = 0;
	setup_base_signals();
	input = readline("Minishell$ ");
	while (input)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			process_input(input, &new_envp, &exit_status);
		}
		input = readline("Minishell$ ");
	}
	free_array(new_envp);
	return (0);
}
