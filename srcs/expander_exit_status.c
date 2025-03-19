#include "../includes/minishell.h"

static char	*replace_exit(char *cmd, char *exit_str, int *i)
{
	char	*rpl;
	size_t	ex_l;
	size_t	c_len;
	size_t	q_len;
	size_t	total_len;

	ex_l = ft_strlen(exit_str);
	c_len = ft_strlen(cmd);
	q_len = ft_strlen("$?");
	total_len = c_len - q_len + ex_l;
	rpl = (char *)ft_calloc(total_len, sizeof(char));
	if (!rpl)
		return (NULL);
	ft_strlcpy(rpl, cmd, *i + 1);
	ft_strlcpy(rpl + *i, exit_str, ex_l + 1);
	ft_strlcpy(rpl + *i + ex_l, cmd + *i + q_len, c_len - *i - q_len + 1);
	*i = *i + ex_l;
	free(exit_str);
	return (rpl);
}

static int	check_exit(char *cmd, char *ex_str, char *change)
{
	int		squote;
	int		i;

	squote = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && squote == 0)
			squote = 1;
		else if (cmd[i] == '\'' && squote == 1)
			squote = 0;
		if (cmd[i] == '$' && squote == 0)
		{
			if (cmd[i + 1] == '?')
			{
				change = replace_exit(cmd, ex_str, &i);
				if (!change)
					return (0);
			}
		}
		i++;
	}
	return (1);
}

void	expand_exit_status(t_command *cmd, int exit_status)
{
	int		i;
	char	*change;
	char	*ex_str;

	i = 0;
	ex_str = ft_itoa(exit_status);
	if (!ex_str)
		cmd_error(cmd, strerror(errno), errno);
	while (cmd->full_cmd_args[i])
	{
		change = NULL;
		if (!check_exit(cmd->full_cmd_args[i], ex_str, change))
			cmd_error(cmd, strerror(errno), errno);
		if (change)
		{
			free(cmd->full_cmd_args[i]);
			cmd->full_cmd_args[i] = change;
			i--;
		}
		i++;
	}
}
