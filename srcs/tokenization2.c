#include "../incs/minishell.h"

void	handle_less_than(const char **ptr, t_token **tokens)
{
	if (*(*ptr + 1) == '<')
	{
		add_token(tokens, TOKEN_HEREDOC, "<<");
		*ptr += 2;
	}
	else
	{
		add_token(tokens, TOKEN_REDIRECT_IN, "<");
		(*ptr)++;
	}
}

void	handle_greater_than(const char **ptr, t_token **tokens)
{
	if (*(*ptr + 1) == '>')
	{
		add_token(tokens, TOKEN_APPEND, ">>");
		*ptr += 2;
	}
	else
	{
		add_token(tokens, TOKEN_REDIRECT_OUT, ">");
		(*ptr)++;
	}
}

/* Helper function to handle quoted values */
static int	handle_quoted_value(const char **ptr, t_data *data)
{
	char	quote;

	quote = **ptr;
	(*ptr)++;
	while (**ptr && **ptr != quote)
		(*ptr)++;
	if (**ptr == quote)
	{
		(*ptr)++;
		return (0);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Unclosed quote detected\n");
		data->exit_parsing = 2;
		return (1);
	}
}

/* Helper function to handle assignment cases */
void	handle_assignment(const char **ptr, t_token **tokens,
				const char *start, t_data *data)
{
	char		*value;

	(*ptr)++;
	if (**ptr == '\'' || **ptr == '"')
		handle_quoted_value(ptr, data);
	else
	{
		while (**ptr && !isspace(**ptr) && **ptr != '|' && **ptr != '<'
			&& **ptr != '>')
			(*ptr)++;
	}
	value = ft_strndup(start, *ptr - start);
	if (!value)
		return ;
	add_token(tokens, TOKEN_WORD, value);
	free(value);
}

/* Helper function to handle non-assignment cases */
void	handle_non_assignment(const char **ptr, t_token **tokens,
				const char *start)
{
	char		*value;

	*ptr = start;
	while (**ptr && !isspace(**ptr) && **ptr != '|' && **ptr != '<'
		&& **ptr != '>')
		(*ptr)++;
	value = ft_strndup(start, *ptr - start);
	if (!value)
		return ;
	add_token(tokens, TOKEN_WORD, value);
	free (value);
}
