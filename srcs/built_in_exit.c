#include "../includes/minishell.h"

void	exit_cmd(t_cmd *cmd, int exit_num)
{
	restore_stdin(cmd);
	free_array(cmd->envp);
	free_all_cmds(cmd);
	rl_clear_history();
	exit((unsigned char)exit_num);
}

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	own_exit(t_cmd *cmd)
{
	int	n;

	if (cmd->pipe_next || cmd->pipe_prev)
		return ;
	else
	{
		if (!cmd->full_cmd_args[1])
			exit_cmd(cmd, cmd->exit_status);
		if (cmd->full_cmd_args[1] && !cmd->full_cmd_args[2])
		{
			if (is_digit(cmd->full_cmd_args[1]))
			{
				n = ft_atoi(cmd->full_cmd_args[1]);
				exit_cmd(cmd, n);
			}
			else
				cmd_error(cmd, " numeric argument required", 2);
		}
		cmd_error(cmd, " too many arguments", EXIT_FAILURE);
	}
}
