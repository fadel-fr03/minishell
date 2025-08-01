#include "../incs/minishell.h"

size_t	handle_dollar_digit(const char *input, t_expander_state *state)
{
	int		index;
	char	*value;

	index = input[state->i + 1] - '0';
	if (index > 0 && index < state->data->exit)
	{
		value = state->data->tokens[index - 1].value;
		if (value)
		{
			ft_strcpy(&state->expanded[state->j], value);
			state->j += ft_strlen(value);
		}
	}
	state->i += 2;
	return (state->i);
}

size_t	handle_dollar_var(const char *input, t_expander_state *state)
{
	char	var_name[100];
	char	*value;
	int		var_len;

	ft_bzero(var_name, sizeof(var_name));
	state->i++;
	var_len = 0;
	while (input[state->i] && (ft_isalnum(input[state->i])
			|| input[state->i] == '_'))
	{
		var_name[var_len++] = input[state->i];
		state->i++;
	}
	var_name[var_len] = '\0';
	value = get_env_value(var_name, state->data->env);
	if (value)
	{
		ft_strcpy(&state->expanded[state->j], value);
		state->j += ft_strlen(value);
		free(value);
	}
	return (state->i);
}
