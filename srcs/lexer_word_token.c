#include "../includes/minishell.h"

static void	double_quote(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
		{	
			(*i)++;
			return ;
		}
		(*i)++;
	}
}

static void	single_quote(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
		{	
			(*i)++;
			return ;
		}
		(*i)++;
	}
}

static void	word_token_helper(char *str, int *i)
{
	while (str[*i] && !(str[*i] == ' ' || str[*i] == '\t' || str[*i] == ';'
			|| str[*i] == '|' || str[*i] == '<' || str[*i] == '>'))
	{
		if (str[*i] == '\'')
		{
			(*i)++;
			single_quote(str, i);
		}
		else if (str[*i] == '\"')
		{
			(*i)++;
			double_quote(str, i);
		}
		else
			(*i)++;
	}
}

int	word_token(char *str, int *i, t_token **token_list)
{
	int		start;
	int		len;
	char	*word;
	t_token	*word_token;

	start = *i;
	word_token_helper(str, i);
	len = *i - start;
	word = ft_strndup(&str[start], len);
	if (!word)
		return (0);
	word_token = create_new_token(word);
	if (!word_token)
	{
		free(word);
		return (0);
	}
	add_token_to_list(token_list, word_token);
	return (1);
}
