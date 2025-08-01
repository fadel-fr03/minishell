#include "../incs/minishell.h"

size_t	handle_dollar_exit(t_expander_state *state)
{
	ft_strcpy(&state->expanded[state->j], state->exit_status_str);
	state->j += ft_strlen(state->exit_status_str);
	state->i += 2;
	return (state->i);
}

size_t	handle_dollar_sign(const char *input, t_expander_state *state)
{
	if (input[state->i + 1] == '?')
		return (handle_dollar_exit(state));
	else if (ft_isdigit(input[state->i + 1]))
		return (handle_dollar_digit(input, state));
	else if (ft_isalnum(input[state->i + 1]) || input[state->i + 1] == '_')
		return (handle_dollar_var(input, state));
	else
	{
		state->expanded[state->j++] = input[state->i++];
		return (state->i);
	}
}

int	check_quotes(char c, t_expander_state *state)
{
	if (c == '\'' && !state->in_double_quotes)
	{
		state->in_single_quotes = !state->in_single_quotes;
		return (1);
	}
	if (c == '\"' && !state->in_single_quotes)
	{
		state->in_double_quotes = !state->in_double_quotes;
		return (1);
	}
	return (0);
}

char	*process_variable_expansion(const char *input,
			t_expander_state *state)
{
	while (input[state->i] != '\0')
	{
		if (check_quotes(input[state->i], state))
			state->i++;
		else if (!state->in_single_quotes && input[state->i] == '$')
			state->i = handle_dollar_sign(input, state);
		else if (!state->in_single_quotes && input[state->i] == '~'
			&& should_expand_tilde(input, state->i))
			state->i = expand_tilde(state);
		else
			state->expanded[state->j++] = input[state->i++];
	}
	state->expanded[state->j] = '\0';
	if (state->home)
		free(state->home);
	return (state->expanded);
}
