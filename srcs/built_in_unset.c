#include "../includes/minishell.h"

void	replace_env(char **envp, int i)
{
	/*char	*temp;

	temp = envp[i];*/
	while (envp[i])
	{
		
		envp[i] = envp[i + 1];
		i++;
	}
	//free(temp); do this once envp copy is created
}

static void	check_env(char *str, char **envp)
{
	size_t	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], len) && envp[i][len] == '=')
		{
			replace_env(envp, i);
			return ;
		}
		i++;
	}
}

void	unset_var(t_command *cmd, char **envp)
{
	int	i;
	char	*temp;

	if (cmd->pipe_next || cmd->pipe_prev)
		return ;
	else
	{
		i = 1;
		while (cmd->full_cmd_args[i])
		{
			temp = cmd->full_cmd_args[i];
			check_env(temp, envp);
			i++;
		}
	}
}