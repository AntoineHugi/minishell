#include "../includes/minishell.h"

static int	check_nl(t_cmd *cmd)
{
	char	*str;

	str = cmd->full_cmd_args[1];
	if (!ft_strncmp(str, "-n", ft_strlen(str)))
		return (1);
	return (0);
}

void	echo(t_cmd *cmd)
{
	int		nl;
	int		i;
	size_t	len;

	nl = 0;
	i = 1;
	if (!cmd->full_cmd_args[i])
		write(STDOUT_FILENO, "\n", 1);
	else
	{
		nl = check_nl(cmd);
		i = i + nl;
		while (cmd->full_cmd_args[i])
		{
			len = ft_strlen(cmd->full_cmd_args[i]);
			write(STDOUT_FILENO, cmd->full_cmd_args[i], len);
			i++;
			if (cmd->full_cmd_args[i])
				write(STDOUT_FILENO, " ", 1);
		}
		if (!nl)
			write(STDOUT_FILENO, "\n", 1);
	}
	cmd->exit_status = 0;
}
