#include "../incs/minishell.h"

/* Refactored handle_word function */
void	handle_word(const char **ptr, t_token **tokens, t_data *data)
{
	const char	*start;

	start = *ptr;
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
		(*ptr)++;
	if (**ptr == '=')
		handle_assignment(ptr, tokens, start, data);
	else
		handle_non_assignment(ptr, tokens, start);
}

void	handle_default(const char **ptr, t_token **tokens)
{
	const char	*start;
	char		*value;

	start = *ptr;
	while (**ptr && !isspace(**ptr) && **ptr != '|' && **ptr != '<'
		&& **ptr != '>')
		(*ptr)++;
	value = ft_strndup(start, *ptr - start);
	if (!value)
		return ;
	add_token(tokens, TOKEN_WORD, value);
	free(value);
}

/* Helper function to handle different token types */
static void	handle_special_tokens(const char **ptr, t_token **tokens,
				t_data *data)
{
	if (**ptr == '\'')
		handle_single_quote(ptr, tokens, data);
	else if (**ptr == '"')
		handle_double_quote(ptr, tokens, data);
	else if (**ptr == '|')
	{
		add_token(tokens, TOKEN_PIPE, "|");
		(*ptr)++;
	}
	else if (**ptr == '<')
		handle_less_than(ptr, tokens);
	else if (**ptr == '>')
		handle_greater_than(ptr, tokens);
	else if (isalpha(**ptr) || **ptr == '_')
		handle_word(ptr, tokens, data);
	else if (**ptr)
		handle_default(ptr, tokens);
}

/* Refactored tokenize function */
t_token	*tokenize(const char *input, t_data *data)
{
	t_token		*tokens;
	const char	*ptr;

	data->exit_parsing = 0;
	tokens = NULL;
	ptr = input;
	while (*ptr)
	{
		ptr = skip_whitespace(ptr);
		if (!*ptr)
			break ;
		if (data->exit_parsing != 0)
			break ;
		handle_special_tokens(&ptr, &tokens, data);
		if (data->exit_parsing != 0)
			break ;
	}
	if (data->exit_parsing != 0)
	{
		if (tokens)
			free_tokens(tokens);
		return (NULL);
	}
	add_token(&tokens, TOKEN_EOF, NULL);
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
