#include "../includes/minishell.h"

void	expand_files(t_command *cmd, char **envp)
{
	char			*change;
	char			*old_name;
	t_redirection	*redir;

	redir = cmd->redir;
	while (redir)
	{
		change = check_envp(redir->name, envp);
		if (change)
		{
			old_name = redir->name;
			redir->name = change;
			free(old_name);
			old_name = NULL;
		}
		redir = redir->next;
	}
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
