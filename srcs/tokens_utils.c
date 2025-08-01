#include "../incs/minishell.h"

void	remove_leading_empty_tokens(t_token **tokens)
{
	t_token	*current;

	while (*tokens && (*tokens)->value && (*tokens)->value[0] == '\0')
	{
		current = *tokens;
		*tokens = (*tokens)->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = NULL;
	}
}
