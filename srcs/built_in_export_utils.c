#include "../includes/minishell.h"

void	print_export(char **envp)
{
	int	i;
	int	j;
	char	temp,

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) < 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		write(1, "export ", 7);
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 2);
		i++;
	}
}

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]))
		i++;
	else
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	else
		return (0);
}

char	**realloc_envp(char ***envp)
{
	char	**new_envp;
	int		len;

	len = 0;
	while ((*envp)[len])
		len++;
	new_envp = (char **)ft_calloc((len + 2), sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (len > 0)
	{
		new_envp[len - 1] = ft_strdup((*envp)[len - 1]);
		if (!new_envp[len - 1])
		{
			free_array(*envp);
			free_array(new_envp);
			return (NULL);
		}
		len--;
	}
	free_array(*envp);
	return (new_envp);
}
