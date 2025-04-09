#include "../includes/minishell.h"

int	pre_parser(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	if (!token || !token->content)
		return (0);
	if (token->content[0] == '|' || ((token->content[0] == '>'
				|| token->content[0] == '<') && !token->next))
	{
		printf("Minishell: syntax error near unexpected token");
		printf("` %s'\n", token->content);
		return (0);
	}
	while (token)
	{
		if ((token->content[0] == '>' || token->content[0] == '<'
				|| token->content[0] == '|')
			&& (!token->next || token->next->content[0] == '|'))
		{
			printf("Minishell: syntax error near unexpected token");
			printf("` %s'\n", token->content);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
