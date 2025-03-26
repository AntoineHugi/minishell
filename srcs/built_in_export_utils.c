#include "../includes/minishell.h"

int	check_valid_key(t_command *cmd, char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]))
		i++;
	else
	{
		cmd->exit_status = 1;
		return (0);
	}
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	else
	{
		cmd->exit_status = 1;
		return (0);
	}
}

