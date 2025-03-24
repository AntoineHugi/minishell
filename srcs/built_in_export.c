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

static char	*generate_env(t_command *cmd, int j, char *key)
{
	size_t	i;
	char	*value;
	char	*input;
	char	*env;

	i = 0;
	input = cmd->full_cmd_args[j];
	while (input[i] != '=')
		i++;
	i++;
	value = (char *)malloc((ft_strlen(input + i) + 1) * sizeof(char));
	if (!value)
		return (NULL);
	parse_value(input + i, value);
	if (!value)
		return (NULL);
	env = ft_strjoin(key, value);
	if (!env)
	{
		free(value);
		return (NULL);
	}
	free(value);
	return (env);
}

/* add case for "export $my_var" */
static char	*get_key(t_command *cmd, int i)
{
	int		j;
	char	*key;
	char	*input;

	j = 0;
	input = cmd->full_cmd_args[i];
	while (input[j] && isalnum(input[j]))
		j++;
	if (input[j] == '=' && j != 0)
		j++;
	else if (!input[j])
		j++;
	else
		export_error(cmd, " : not a valid identifier", 1);
	key = (char *)malloc((j + 1) * sizeof(char));
	if (!key)
		cmd_error(cmd, strerror(errno), errno);
	ft_strlcpy(key, input, j);
	return (key);
}

void	export_var(t_command *cmd, char **envp)
{
	char	*env;
	char	*key;
	int		i;

	i = 1;	
	while (cmd->full_cmd_args[i])
	{
		key = get_key(cmd, i);
		if (key)
		{
			env = generate_env(cmd, i, key);
			if (!env)
			{
				free(key);
				cmd_error(cmd, strerror(errno), errno);
			}
			set_env(key, env, envp);
		}
		i++;
	}
	/*else
		print_error(cmd->full_cmd_args[1], 1);*/
}
