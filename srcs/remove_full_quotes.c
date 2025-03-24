#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*malloc_len_minus_quotes(t_command *cmd, int i)
{
	char	*string;
	int		j;
	int		len;
	int		count;


	len = ft_strlen(cmd->full_cmd_args[i]);
	j = 0;
	count = 0;
	while (cmd->full_cmd_args[i][j])
	{
		if (cmd->full_cmd_args[i][j] == 34 || cmd->full_cmd_args[i][j] == 39)
			count++;
		j++;
	}

	string = malloc(sizeof(char) * (len - count + 1));
	if (!string)
		return (NULL);
	return (string);
}

int	remove_quotes_util(t_command *cmd, int i)
{
	int			j;
	int			k;
	char		*string;

	if (!(string = malloc_len_minus_quotes(cmd, i)))
		return (0);
	j = 0;
	k = 0;
	while (cmd->full_cmd_args[i][j])
	{
		if (cmd->full_cmd_args[i][j] == 34 || cmd->full_cmd_args[i][j] == 39)
			j++;
		else
		{
			string[k] = cmd->full_cmd_args[i][j];
			j++;
			k++;
		}
	}
	string[k] = '\0';
	free(cmd->full_cmd_args[i]);
	cmd->full_cmd_args[i] = string;
	return (1);
}

// int	remove_quotes(t_command **cmd_list)
// {
// 	t_command	*cmd;
// 	int			i;

// 	cmd = *cmd_list;
// 	while (cmd != NULL)
// 	{
// 		i = -1;
// 		while (cmd->full_cmd_args[++i])
// 		{
// 			if (cmd->full_cmd_args[i] && ft_strchr(cmd->full_cmd_args[i], 34))
// 				if (!remove_quotes_util(cmd, i))
// 					return (0);

// 			if (cmd->full_cmd_args[i] && ft_strchr(cmd->full_cmd_args[i], 39))
// 			{
// 				if (!remove_quotes_util(cmd, i))
// 					return (0);
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (1);
// }

int	find_quote_type(t_command *cmd, int i, int *y)
{
	int	*y;
	int	quote_type;

	quote_type = 0;
	while (cmd->full_cmd_args[i][*y])
	{
		if (cmd->full_cmd_args[i][*y] == 34)
		{
			quote_type = 2;
			break ;
		}
		else if (cmd->full_cmd_args[i][*y] == 39)
		{
			quote_type = 1;
			break ;
		}
		(*y)++;
	}
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
			if (cmd->full_cmd_args[i][0] == 34)
				if (!remove_quotes_util(cmd, i))
					return (0);

			if (cmd->full_cmd_args[i] && ft_strchr(cmd->full_cmd_args[i], 39))
			{
				if (!remove_quotes_util(cmd, i))
					return (0);
			}
		}
		cmd = cmd->next;
	}
	return (1);
}
