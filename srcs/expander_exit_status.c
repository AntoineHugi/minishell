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
	ft_strlcpy(rpl, cmd, *i + 1);
	ft_strlcpy(rpl + *i, exit_str, ex_l + 1);
	ft_strlcpy(rpl + *i + ex_l, cmd + *i + q_len, c_len - *i - q_len + 1);
	*i = *i + ex_l;
	free(exit_str);
	return (rpl);
}

static char	*check_exit(char *cmd, int exit_status)
{
	int		squote;
	int		i;
	char	*change;
	char	*ex_str;

	squote = 0;
	i = 0;
	change = NULL;
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
				ex_str = ft_itoa(exit_status);
				change = replace_exit(cmd, ex_str, &i);
			}
		}
		i++;
	}
	return (change);
}

void	expand_exit_status(t_command *cmd, int exit_status)
{
	int		i;
	char	*change;

	i = 0;
	while (cmd->full_cmd_args[i])
	{
		change = check_exit(cmd->full_cmd_args[i], exit_status);
		if (change)
		{
			free(cmd->full_cmd_args[i]);
			cmd->full_cmd_args[i] = change;
			i--;
		}
		i++;
	}
}
