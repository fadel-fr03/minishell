#include "../incs/minishell.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token_type type, const char *value)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_token(type, value);
	if (!new_token)
	{
		perror("Failed to create token");
		exit(EXIT_FAILURE);
	}
	if (!*tokens)
		*tokens = new_token;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

char	*str_append(char *original, const char *to_append)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!original)
		return (ft_strdup(to_append));
	len1 = ft_strlen(original);
	len2 = ft_strlen(to_append);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, original);
	ft_strcat(new_str, to_append);
	free(original);
	return (new_str);
}

char	*collect_quoted_segment(const char **ptr, char quote, t_data *data)
{
	const char	*start;
	char		*segment;

	start = *ptr - 1;
	while (**ptr && **ptr != quote)
		(*ptr)++;
	if (**ptr == quote)
	{
		(*ptr)++;
		segment = ft_strndup(start, *ptr - start);
		return (segment);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Unclosed quote detected\n");
		data->exit_parsing = 2;
		return (NULL);
	}
}

char	*collect_unquoted_word(const char **ptr)
{
	const char	*start;
	char		*segment;

	start = *ptr;
	while (**ptr && !ft_isspace(**ptr) && **ptr != '|' && **ptr != '<'
		&& **ptr != '>' && **ptr != '"' && **ptr != '\'')
		(*ptr)++;
	if (*ptr > start)
	{
		segment = ft_strndup(start, *ptr - start);
		return (segment);
	}
	return (NULL);
}
