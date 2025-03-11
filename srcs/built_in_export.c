#include "../includes/minishell.h"

void	set_env(char *key, char *env, char **envp)
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

static void	parse_value(char *src, char *dest)
{
	int		squote;
	int		dquote;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	squote = 0;
	dquote = 0;
	while (src[++i])
	{
		if (src[i] == '\\' && !squote && !dquote)
		{
			i++;
			if (src[i])
				dest[j++] = src[i];
        }
		else if (src[i] == '\'' && !dquote) 
			squote = !squote;
		else if (src[i] == '"' && !squote)
			dquote = !dquote;
		else
			dest[j++] = src[i];
	}
	dest[j] = '\0';
}

char	*generate_env(char *input, char *key)
{
	size_t	i;
	char	*value;
	char	*env;

	i = 0;
	while (input[i] != '=')
		i++;
	i++;
	value = (char *)malloc((ft_strlen(input + i) + 1) * sizeof(char));
	if (!value)
		return (NULL);
	parse_value(input + i, value);
	env = ft_strjoin(key, value);
	free(value);
	return (env);
}

static char	*get_key(char *input)
{
	int		i;
	char	*key;

	i = 0;
	while (input[i] && isalnum(input[i]))
		i++;
	if (input[i] == '=' && i != 0)
		i++;
	else
		return (NULL);
	key = (char *)malloc((i + 1) * sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, input, i);
	return (key);
}

void	export_var(t_command *cmd, char **envp)
{
	int		i;
	char	*env;
	char	*key;

	if (!cmd->full_cmd_args[1])
		return ;
	key = get_key(cmd->full_cmd_args[1]);
	if (key)
	{
		env = generate_env(cmd->full_cmd_args[1], key);
		if (!env)
		{
			free(key);
			print_error(cmd->full_cmd_args[1], 1);
		}
		set_env(key, env, envp);
	}
	else
		print_error(cmd->full_cmd_args[1], 1);
}
