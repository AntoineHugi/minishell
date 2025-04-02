#include "../includes/minishell.h"

static int	check_nl(t_command *cmd)
{
	char	*str;

	str = cmd->full_cmd_args[1];
	if (!ft_strncmp(str, "-n", ft_strlen(str)))
		return (1);
	return (0);
}

void	echo(t_command *cmd)
{
	int		nl;
	int		i;

	nl = 0;
	i = 1;
	if (!cmd->full_cmd_args[i])
		printf("\n");
	else
	{
		nl = check_nl(cmd);
		i = i + nl;
		while (cmd->full_cmd_args[i])
		{
			printf("%s", cmd->full_cmd_args[i]);
			i++;
			if (cmd->full_cmd_args[i])
				printf(" ");
		}
		if (!nl)
			printf("\n");
	}
	cmd->exit_status = 0;
}
