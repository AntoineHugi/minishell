#include "../includes/minishell.h"

static void	set_env(t_cmd *cmd, char *key, char *env, char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, ft_strlen(key)))
		{
			free((*envp)[i]);
			(*envp)[i] = env;
			free(key);
			return ;
		}
		else
			i++;
	}
	free(key);
	*envp = realloc_envp(envp);
	if (!(*envp))
		cmd_error(cmd, strerror(errno), errno);
	(*envp)[i] = env;
}

static char	*generate_value(t_cmd *cmd, char *key, char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
		i++;
	else
		return (NULL);
	value = (char *)malloc((ft_strlen(str + i) + 1) * sizeof(char));
	if (!value)
	{
		free(key);
		cmd_error(cmd, strerror(errno), errno);
	}
	ft_memcpy(value, str + i, ft_strlen(str + i));
	value[ft_strlen(str + i)] = '\0';
	return (value);
}

static char	*generate_key(t_cmd *cmd, char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[i] == '=')
		i++;
	key = (char *)malloc((i + 1) * sizeof(char));
	if (!key)
		cmd_error(cmd, strerror(errno), errno);
	ft_memcpy(key, str, i);
	key[i] = '\0';
	return (key);
}

static void	generate_env(t_cmd *cmd, char *arg, char ***envp)
{
	char	*env;
	char	*value;
	char	*key;

	key = generate_key(cmd, arg);
	value = generate_value(cmd, key, arg);
	if (value)
	{
		env = ft_strjoin(key, value);
		if (!env)
		{
			free(key);
			free(value);
			cmd_error(cmd, strerror(errno), errno);
		}
		free(value);
		set_env(cmd, key, env, envp);
	}
	else
		free(key);
}

void	export_var(t_cmd *cmd, char ***envp)
{
	int		i;
	int		failed;

	failed = 0;
	i = 1;
	if (!cmd->full_cmd_args[i])
	{
		cmd->exit_status = 0;
		return ;
	}
	while (cmd->full_cmd_args[i])
	{
		if (!check_valid_key(cmd->full_cmd_args[i]))
		{
			failed = 1;
			print_error("Minishell: export: not a valid identifier");
		}
		else
			generate_env(cmd, cmd->full_cmd_args[i], envp);
		i++;
	}
	if (failed == 1)
		cmd->exit_status = 1;
	else
		cmd->exit_status = 0;
}
