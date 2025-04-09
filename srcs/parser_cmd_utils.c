#include "../includes/minishell.h"

void	verify_built_in(t_cmd *new_cmd)
{
	char		*string;
	const char	*built_in[] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	int			i;

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

void	verify_executable(t_cmd *new_cmd)
{
	if (access(new_cmd->full_cmd_args[0], X_OK) == 0)
		new_cmd->executable = 1;
	else
		new_cmd->executable = 0;
}

void	verify_pipe_prev(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = *cmd_list;
	while (current_cmd && current_cmd->next != NULL)
		current_cmd = current_cmd->next;
	if (current_cmd->pipe_next)
		new_cmd->pipe_prev = 1;
	else
		new_cmd->pipe_prev = 0;
}

void	verify_cmd_specs(t_cmd **cmd_list, t_cmd *new_cmd)
{
	verify_built_in(new_cmd);
	verify_executable(new_cmd);
	verify_pipe_prev(cmd_list, new_cmd);
}
