#include "../includes/minishell.h"

static void	trimmed_str(char *src, char *dst, int quote_type)
{
	int	j;
	int	count;
	int	k;

	j = 0;
	count = 0;
	k = 0;
	while (src[j])
	{
		if (src[j] == quote_type && count < 2)
			count++;
		else
		{
			dst[k] = src[j];
			k++;
		}
		j++;
	}
	dst[k] = '\0';
}

static char	*create_new_str(char *str, int *y, int *quote_type)
{
	char		*new;

	new = malloc(sizeof(char) * (ft_strlen(str) - 2 + 1));
	if (!new)
		return (NULL);
	trimmed_str(str, new, *quote_type);
	*y = *y - 2;
	*quote_type = 0;
	return (new);
}

static int	check_if_quote_ends(char *str, int *y, int quote_type)
{
	while (str[*y])
	{
		if (str[*y] == quote_type)
			return (1);
		(*y)++;
	}
	return (0);
}

static int	find_quote_type(char *str, int *y)
{
	while (str[*y])
	{
		if (str[*y] == '\"')
		{
			(*y)++;
			return (34);
		}
		else if (str[*y] == '\'')
		{
			(*y)++;
			return (39);
		}
		(*y)++;
	}
	return (0);
}

char	*quotes_inspection(char *str, int *y)
{
	int			quote_type;
	char		*new;

	quote_type = find_quote_type(str, y);
	if (quote_type)
	{
		if (check_if_quote_ends(str, y, quote_type))
		{
			new = create_new_str(str, y, &quote_type);
			if (!new)
				return (NULL);
			else
				return (new);
		}
	}
	return (str);
}
