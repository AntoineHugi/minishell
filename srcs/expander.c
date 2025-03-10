#include "../includes/minishell.h"

void	expand_files(t_command *cmd, char **envp)
{
	char	*change;

	if (cmd->input)
	{
		change = check_env(cmd->input->name, envp);
		if (change)
			cmd->input->name = change;
	}
	if (cmd->output)
	{
		change = check_env(cmd->output->name, envp);
		if (change)
			cmd->output->name = change;
	}
}

void	expand_cmd(t_command *cmd, char **envp)
{
	int		i;
	char	*change;

	i = 0;	
	while (cmd->full_cmd_args[i])
	{
		change = check_env(cmd->full_cmd_args[i], envp);
		if (change)
		{
			free(cmd->full_cmd_args[i]);
			cmd->full_cmd_args[i] = change;
		}
		i++;
	}
}

int	expander(t_command *cmd, char **envp)
{
	while (cmd)
	{
		expand_cmd(cmd, envp);
		expand_files(cmd, envp);
		cmd = cmd->next;
	}
	return (0);
}
