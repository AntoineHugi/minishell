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

void	free_redirect(t_redirection *redirect)
{
	t_redirection *temp;
	
	while (redirect)
	{
		temp = redirect->next;
		free(redirect->name);
		free(redirect);
		redirect = temp;
	}
}

void	free_cmd(t_command *cmd)
{
	if (cmd->full_cmd_args)
		free_array((cmd->full_cmd_args));
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->input)
		free_redirect(cmd->input);
	if (cmd->output)
		free_redirect(cmd->output);
	close(cmd->og_stdin);
	close(cmd->og_stdout);
	free(cmd);
}

void	free_all_cmds(t_command *cmd)
{
	t_command	*next;

	while (cmd)
	{
		next = cmd->next;
		free_cmd(cmd);
		cmd = next;
	}
}
