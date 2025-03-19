#include "../includes/minishell.h"

static void	add_token_to_list(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		last = token_last(*token);
		last->next = new;
	}
}

static int	quote_token(char *str, int *i, t_token **token_list)
{
	char	quote_type;
	int		start;
	int		len;
	char	*quote;
	t_token	*quote_token;

	quote_type = 34;
	if (str[*i] == 39)
		quote_type = 39;
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	len = *i - start + 1;
	quote = ft_strndup(&str[start], len);
	if (!quote)
		return (0);
	quote_token = create_new_token(quote);
	if (!quote_token)
	{
		free(quote);
		return (0);
	}
	add_token_to_list(token_list, quote_token);
	return (1);
}

static int	word_token(char *str, int *i, t_token **token_list)
{
	int		start;
	int		len;
	char	*word;
	t_token	*word_token;

	start = *i;
	while (str[*i] && !(str[*i] == ' ' || str[*i] == ';'))
		(*i)++;
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

static int	semicolon_token(char *str, int *i, t_token **token_list)
{
	int		start;
	int		len;
	char	*word;
	t_token	*word_token;

	start = *i;
	(*i)++;
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


t_token	*lexer(char *str)
{
	int		i;
	t_token	*token_list;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_token(str, &i, &token_list);
			i++;
		}
		else if (str[i] == ' ')
			i++;
		else if (str[i] == ';')
			semicolon_token(str, &i, &token_list);
		else
			word_token(str, &i, &token_list);
	}
	return (token_list);
}
