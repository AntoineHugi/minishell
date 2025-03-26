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
