#include "../includes/minishell.h"

void	expand_files(t_command *cmd, char **envp)
{
	char			*change;
	t_redirection	*start;

	if (cmd->redir)
		start = cmd->redir;
	while (cmd->redir)
	{
		change = check_envp(cmd->redir->name, envp);
		if (change)
			cmd->redir->name = change;
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
}

void	expand_cmd(t_command *cmd, char **envp)
{
	int		i;
	char	*change;

	i = 0;
	while (cmd->full_cmd_args[i])
	{
		change = check_envp(cmd->full_cmd_args[i], envp);
		if (change)
		{
			free(cmd->full_cmd_args[i]);
			cmd->full_cmd_args[i] = change;
			i--;
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
