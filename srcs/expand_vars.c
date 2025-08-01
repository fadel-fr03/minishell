#include "../incs/minishell.h"

char	*get_home_directory(t_data *data)
{
	char	*home;

	home = get_env_value("HOME", data->env);
	if (home)
		return (home);
	return (ft_strdup(""));
}

char	*initialize_expansion_buffer(const char *input)
{
	size_t	input_len;
	char	*expanded;

	input_len = ft_strlen(input);
	expanded = (char *)malloc(input_len * 256);
	return (expanded);
}

const char	*get_exit_status_str(t_data *data)
{
	static char	exit_status_str[12];

	ft_sprintf(exit_status_str, "%d", data->exit_status);
	return (exit_status_str);
}

char	*expand_variable(const char *input, t_data *data)
{
	char				*expanded;
	t_expander_state	state;

	expanded = initialize_expansion_buffer(input);
	if (!expanded)
		return (NULL);
	state.expanded = expanded;
	state.i = 0;
	state.j = 0;
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	state.exit_status_str = get_exit_status_str(data);
	state.home = get_home_directory(data);
	state.data = data;
	return (process_variable_expansion(input, &state));
}

void	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*current;
	t_token	*previous;
	char	*expanded_value;

	current = *tokens;
	previous = NULL;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (previous && previous->type == TOKEN_HEREDOC)
			{
				previous = current;
				current = current->next;
				continue ;
			}
			expanded_value = expand_variable(current->value, data);
			if (handle_expanded_value(&current, &previous, expanded_value,
					tokens))
				continue ;
		}
		previous = current;
		current = current->next;
	}
}
