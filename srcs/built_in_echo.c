#include "../includes/minishell.h"

void	echo(t_command *cmd)
{
	int		nl;
	int		i;
	char	*str;

	nl = 0;
	i = 1;
	str = cmd->full_cmd_args[i];
	if (!ft_strncmp(str, "-n", ft_strlen(str)))
	{
		nl = 1;
		i++;
	}
	while (cmd->full_cmd_args[i])
	{
		printf("%s", cmd->full_cmd_args[i]);
		i++;
		if (cmd->full_cmd_args[i])
			printf(" ");
	}
	if (!nl)
		printf("\n");
	cmd->exit_status = 0;
}
