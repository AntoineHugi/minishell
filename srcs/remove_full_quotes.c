#include "../includes/minishell.h"
#include "../libft/libft.h"

int	remove_quotes_util(t_command *cmd, int i, int *y, int *quote_type)
{
	int			j;
	int			k;
	char		*string;
	int			count;

	if (!(string = malloc(sizeof(char) *
		(ft_strlen(cmd->full_cmd_args[i]) - 2 + 1))))
		return (0);
	j = -1;
	k = 0;
	count = 0;
	while (cmd->full_cmd_args[i][++j])
	{
		if (cmd->full_cmd_args[i][j] == *quote_type && count < 2)
			count++;
		else
		{
			string[k] = cmd->full_cmd_args[i][j];
			k++;
		}
	}
	string[k] = '\0';
	free(cmd->full_cmd_args[i]);
	cmd->full_cmd_args[i] = string;
	return ((*y) -= 2, (*quote_type) = 0, 1);
}

int	find_quote_type(t_command *cmd, int i, int *y)
{
	while (cmd->full_cmd_args[i][*y])
	{
		if (cmd->full_cmd_args[i][*y] == 34)
			return ((*y)++, 34);
		else if (cmd->full_cmd_args[i][*y] == 39)
			return ((*y)++, 39);
		(*y)++;
	}
	return (0);
}

int	check_if_quote_ends(t_command *cmd, int i, int *y, int quote_type)
{
	while (cmd->full_cmd_args[i][*y])
	{
		if (cmd->full_cmd_args[i][*y] == quote_type)
			return (1);
		(*y)++;
	}
	return (0);
}

int	remove_full_quotes(t_command **cmd_list)
{
	t_command	*cmd;
	int			i;
	int			y;
	int			quote_type;

	cmd = *cmd_list;
	while (cmd != NULL)
	{
		i = -1;
		while (cmd->full_cmd_args[++i])
		{
			y = 0;
			while (cmd->full_cmd_args[i][y])
			{
				quote_type = find_quote_type(cmd, i, &y);
				if (quote_type)
				{
					if (check_if_quote_ends(cmd, i, &y, quote_type))
						remove_quotes_util(cmd, i, &y, &quote_type);
				}
			}
		}
		cmd = cmd->next;
	}
	return (1);
}
