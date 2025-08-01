#include "../incs/minishell.h"

void	handle_single_quote(const char **ptr, t_token **tokens, t_data *data)
{
	const char	*start;
	char		*token_value;
	char		quote;

	quote = **ptr;
	(*ptr)++;
	start = *ptr - 1;
	while (**ptr && **ptr != quote)
		(*ptr)++;
	if (**ptr == quote)
	{
		(*ptr)++;
		token_value = ft_strndup(start, *ptr - start);
		add_token(tokens, TOKEN_WORD, token_value);
		free(token_value);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Unclosed single quote detected\n");
		data->exit_parsing = 2;
	}
}

/* Helper function to process unquoted words and additional quoted segments */
void	process_segments(const char **ptr, char **final_str, t_data *data)
{
	char	*segment;
	char	quote;

	while (1)
	{
		segment = collect_unquoted_word(ptr);
		if (segment)
		{
			*final_str = str_append(*final_str, segment);
			free(segment);
		}
		if (**ptr == '"' || **ptr == '\'')
		{
			quote = **ptr;
			(*ptr)++;
			segment = collect_quoted_segment(ptr, quote, data);
			*final_str = str_append(*final_str, segment);
			free(segment);
		}
		else
			break ;
	}
}

/* Refactored handle_double_quote function */
void	handle_double_quote(const char **ptr, t_token **tokens, t_data *data)
{
	char	*final_str;
	char	*segment;
	char	quote;

	final_str = NULL;
	quote = **ptr;
	(*ptr)++;
	segment = collect_quoted_segment(ptr, quote, data);
	if (!segment)
	{
		data->exit_parsing = 2;
		return ;
	}
	final_str = str_append(final_str, segment);
	free(segment);
	process_segments(ptr, &final_str, data);
	if (data->exit_parsing != 0)
	{
		free(final_str);
		return ;
	}
	add_token(tokens, TOKEN_WORD, final_str);
	free(final_str);
}
