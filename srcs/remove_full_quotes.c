#include "../includes/minishell.h"


static int	remove_full_quotes_redir(t_redirection *redir)
{
	int		y;
	char	*new;

	while (redir)
	{
		y = 0;
		while (redir->name[y])
		{
			new = quotes_inspection(redir->name, &y);
			if (!new)
				return (0);
			if (strncmp(redir->name, new, ft_strlen(redir->name)))
			{
				free(redir->name);
				redir->name = new;
			}
		}
		redir = redir->next;
	}
	return (1);
}

static int	remove_full_quotes_args(char **cmd_arg)
{
	int		i;
	int		y;
	char	*new;

	i = 0;
	while (cmd_arg[i])
	{
		y = 0;
		while (cmd_arg[i][y])
		{
			new = quotes_inspection(cmd_arg[i], &y);
			if (!new)
				return (0);
			if (strncmp(cmd_arg[i], new, ft_strlen(cmd_arg[i])))
			{
				free(cmd_arg[i]);
				cmd_arg[i] = new;
			}
		}
		i++;
	}
	return (1);
}

int	remove_full_quotes(t_command **cmd_list)
{
	t_command	*cmd;

	cmd = *cmd_list;
	while (cmd != NULL)
	{
		if (!remove_full_quotes_args(cmd->full_cmd_args))
			return (0);
		if (!remove_full_quotes_redir(cmd->input))
			return (0);
		if (!remove_full_quotes_redir(cmd->output))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}