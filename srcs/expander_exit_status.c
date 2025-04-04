#include "../includes/minishell.h"

static char	*generate_replacement(char *cmd, char *exit_str, int j)
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
	rpl = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (!rpl)
		return (NULL);
	ft_memcpy(rpl, cmd, j);
	ft_memcpy(rpl + j, exit_str, ex_l);
	ft_memcpy(rpl + j + ex_l, cmd + j + q_len, c_len - j - q_len);
	rpl[total_len] = '\0';
	return (rpl);
}

static int	check_for_exit(char *cmd)
{
	int		squote;
	int		j;

	squote = 0;
	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\'' && squote == 0)
			squote = 1;
		else if (cmd[j] == '\'' && squote == 1)
			squote = 0;
		if (cmd[j] == '$' && squote == 0)
		{
			if (cmd[j + 1] && cmd[j + 1] == '?')
				return (j + 1);
		}
		j++;
	}
	return (0);
}

void	replace_exit_status(t_cmd *cmd, int i, char *change)
{
	free(cmd->full_cmd_args[i]);
	cmd->full_cmd_args[i] = change;
}

void	expand_exit_status(t_cmd *cmd, int exit_status)
{
	int		i;
	int		j;
	char	*ex_str;
	char	*change;

	i = 0;
	ex_str = ft_itoa(exit_status);
	if (!ex_str)
		cmd_error(cmd, strerror(errno), errno);
	while (cmd->full_cmd_args[i])
	{
		j = check_for_exit(cmd->full_cmd_args[i]);
		if (j)
		{
			change = generate_replacement(cmd->full_cmd_args[i], ex_str, j - 1);
			if (!change)
				cmd_error(cmd, strerror(errno), errno);
			else
				replace_exit_status(cmd, i, change);
			i--;
		}
		i++;
	}
	free(ex_str);
}
