#include "../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

void	free_redirect(t_redirection **redirect)
{
	t_redirection	*temp;

	while (*redirect)
	{
		temp = (*redirect)->next;
		free((*redirect)->name);
		free(*redirect);
		*redirect = temp;
	}
	*redirect = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->full_cmd_args)
		free_array((cmd->full_cmd_args));
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->redir)
		free_redirect(&(cmd->redir));
	close(cmd->og_stdin);
	close(cmd->og_stdout);
	free(cmd);
}

void	free_all_cmds(t_cmd *cmd)
{
	t_cmd	*next;

	if (cmd)
		free_array(cmd->envp);
	while (cmd)
	{
		next = cmd->next;
		free_cmd(cmd);
		cmd = next;
	}
}
