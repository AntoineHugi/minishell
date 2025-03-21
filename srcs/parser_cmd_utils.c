#include "../includes/minishell.h"

void	verify_built_in(t_command *new_cmd)
{
	char		*string;
	const char	*built_in[] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", "cat", "grep", "mkdir", "touch",
		"rm", "find", "diff", "export", "sort", "uniq", "head", "tee", "less", "env", NULL};
	int	i;

	string = new_cmd->full_cmd_args[0];
	new_cmd->built_in = 0;
	i = 0;
	while (built_in[i])
	{
		if (ft_strncmp(string, built_in[i], ft_strlen(string)) == 0)
		{
			new_cmd->built_in = 1;
			return ;
		}
		i++;
	}
}

void	verify_executable(t_command *new_cmd)
{
	if (access(new_cmd->full_cmd_args[0], X_OK) == 0)
		new_cmd->executable = 1;
	else
		new_cmd->executable = 0;
}

void	verify_pipe_prev(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*current_cmd;

	printf("	verify_pipe_prev entered. \n");
	current_cmd = *cmd_list;
	if (current_cmd->next == NULL)
		printf("	current_cmd->next is NULL. \n");
	else
	{
		printf("	current_cmd->next is NOT NULL. \n");
		printf("	Arg 0 from next cmd: %s \n", current_cmd->next->full_cmd_args[0]);
	}
	printf("	Current command address: %p\n", (void *)current_cmd);
	printf("	Next command address: %p\n", (void *)current_cmd->next);
	while (current_cmd && current_cmd->next != NULL)
		current_cmd = current_cmd->next;
	printf("	We're now at the end of the current cmd list. \n");
	if (current_cmd->pipe_next)
		new_cmd->pipe_prev = 1;
	else
		new_cmd->pipe_prev = 0;
}
