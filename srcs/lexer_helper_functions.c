#include "../includes/minishell.h"

t_token	*create_new_token(char *content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

void delete_token_list(t_token **token_list)
{
	t_token	*current_token;
	t_token	*last_token;

	if (!(*token_list) || !token_list)
		return ;
	current_token = *token_list;
	while (current_token->next)
	{
		last_token = current_token;
		current_token = current_token->next;
		free(last_token);
	}
	free(current_token);
	(*token_list) = NULL;
}
