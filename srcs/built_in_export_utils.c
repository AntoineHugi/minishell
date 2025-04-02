#include "../includes/minishell.h"

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]))
		i++;
	else
		return (0);
	while (str[i] && ft_isalnum(str[i]))
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
