#include "../includes/minishell.h"

static void	set_env(char *key, char *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			free(envp[i]);
			envp[i] = env;
			free(key);
			return ;
		}
		else
			i++;
	}
	envp[i] = env;
	envp[i + 1] = NULL;
	free(key);
}

static char	*generate_env(t_command *cmd, char *key, char *value)
{
	char	*env;

	env = ft_strjoin(key, value);
	if (!env)
	{
		free(key);
		free(value);
		cmd_error(cmd, strerror(errno), errno);
	}
	free(value);
	return (env);
}

static char	*generate_value(t_command *cmd, char *str)
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
	if (str[i] == '\0')
		return (NULL);
	value = (char *)malloc((ft_strlen(str + i) + 1) * sizeof(char));
	if (!value)
		cmd_error(cmd, strerror(errno), errno);
	ft_memcpy(str + i, value, ft_strlen(str + i));
	value[ft_strlen(str + i)] = '\0';
	return (value);
}

static char	*generate_key(t_command *cmd, char *str)
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
	ft_strlcpy(key, str, i);
	key[i] = '\0';
	return (key);
}


void	export_var(t_command *cmd, char **envp)
{
	char	*value;
	char	*key;
	char	*env;
	int		i;

	i = 1;
	while (cmd->full_cmd_args[i])
	{
		if (!check_valid_key(cmd, cmd->full_cmd_args[i]))
			print_error(" : not a valid identifier\n");
		else
		{
			key = generate_key(cmd, cmd->full_cmd_args[i]);
			value = generate_value(cmd, cmd->full_cmd_args[i]);
			if (value)
			{
				env = generate_env(cmd, key, value);
				set_env(key, env, envp);
			}
		}
		i++;
	}
}
