#include "../includes/minishell.h"

int	pre_parser(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	if (token->content[0] == '|' || ((token->content[0] == '>'
			|| token->content[0] == '<') && !token->next))
		return (printf("Minishell: syntax error near unexpected token `%s'\n", token->content), 0);
	while (token)
	{
		if ((token->content[0] == '>' || token->content[0] == '<'
				|| token->content[0] == '|')
			&& (!token->next || token->next->content[0] == '|'))
			return (printf("Minishell: syntax error near unexpected token `%s'\n", token->content), 0);
		token = token->next;
	}
	return (1);
}
