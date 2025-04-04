#include "../includes/minishell.h"

static char	*replace_env(char *cmd, char *alias, char *env, int *i)
{
	ssize_t	len;
	char	*replacement;

	if (!env)
	{
		free(alias);
		return (NULL);
	}
	len = ft_strlen(cmd) - ft_strlen(alias) + 1 + ft_strlen(env);
	replacement = (char *)ft_calloc(len + 1, sizeof(char));
	ft_memcpy(replacement, cmd, *i);
	ft_memcpy(replacement + *i, env, ft_strlen(env));
	ft_memcpy(replacement + *i + ft_strlen(env),
		cmd + *i + ft_strlen(alias) + 1,
		ft_strlen(cmd) - *i - ft_strlen(alias) - 1);
	replacement[len] = '\0';
	*i = *i + ft_strlen(env);
	free(alias);
	return (replacement);
}

static char	*find_env(char *alias, char **envp)
{
	int		i;
	ssize_t	len;

	len = ft_strlen(alias);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], alias, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return ("");
}

static char	*get_name(char *cmd)
{
	int		i;
	char	*alias;

	i = 0;
	while (ft_isalnum(cmd[i]))
		i++;
	if (i == 0)
		return (NULL);
	alias = (char *)ft_calloc(i + 1, sizeof(char));
	if (!alias)
		return (NULL);
	ft_strlcpy(alias, cmd, i + 1);
	return (alias);
}

char	*check_envp(char *cmd, char **envp)
{
	int		squote;
	int		i;
	char	*alias;

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
			alias = get_name(cmd + i + 1);
			if (alias)
				return (replace_env(cmd, alias, find_env(alias, envp), &i));
		}
		i++;
	}
	return (NULL);
}

void	clean_empty_argument(t_cmd *cmd)
{
	char	*temp;
	int		i;

	while (cmd)
	{
		while (cmd->full_cmd_args[0] && cmd->full_cmd_args[0][0] == '\0')
		{
			i = 0;
			temp = cmd->full_cmd_args[0];
			while (cmd->full_cmd_args[i])
			{
				cmd->full_cmd_args[i] = cmd->full_cmd_args[i + 1];
				i++;
			}
			free(temp);
		}
		cmd = cmd->next;
	}
}
