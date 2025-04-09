#include "../includes/minishell.h"

int	pre_parser(t_token *token_list)
{
	t_token	*token;
	t_token	*next_token;

	token = token_list;
	if (token->content[0] == '|' || ((token->content[0] == '>'
			|| token->content[0] == '<') && !token->next))
		return (printf("Minishell: syntax error near unexpected token `%s'\n", token->content), 0);
	if (!token->next)
		return (1);
	next_token = token->next;
	while (next_token != NULL)
	{
		if ((token->content[0] == '>' || token->content[0] == '<'
				|| token->content[0] == '|') && next_token->content[0] == '|')
			return (printf("Minishell: syntax error near unexpected token `%s'\n", token->content), 0);
		token = token->next;
		next_token = next_token->next;
	}
	return (1);
}
