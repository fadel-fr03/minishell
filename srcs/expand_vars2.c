#include "../incs/minishell.h"

void	remove_empty_token(t_token **current,
			t_token **previous, t_token **tokens)
{
	if (*previous)
		(*previous)->next = (*current)->next;
	else
		*tokens = (*current)->next;
	free((*current)->value);
	free(*current);
	if (*previous)
		*current = (*previous)->next;
	else
		*current = *tokens;
}

int	handle_expanded_value(t_token **current,
			t_token **previous, char *expanded_value,
			t_token **tokens)
{
	(void)previous;
	(void)tokens;
	if (expanded_value)
	{
		if (expanded_value[0] == '\0')
		{
			free((*current)->value);
			(*current)->value = ft_strdup("");
			free(expanded_value);
		}
		else
		{
			free((*current)->value);
			(*current)->value = expanded_value;
		}
	}
	return (0);
}

size_t	expand_tilde(t_expander_state *state)
{
	ft_strcpy(&state->expanded[state->j], state->home);
	state->j += ft_strlen(state->home);
	state->i++;
	return (state->i);
}

int	should_expand_tilde(const char *input, size_t i)
{
	if (i == 0)
	{
		if (input[i + 1] == '/' || input[i + 1] == '\0')
			return (1);
	}
	else
	{
		if (input[i - 1] == ' '
			&& (input[i + 1] == '/' || input[i + 1] == '\0'))
			return (1);
	}
	return (0);
}

size_t	expand_variable_name(const char *input,
			t_expander_state *state)
{
	char		var_name[100];
	int			var_len;
	char		*var_value;

	var_len = 0;
	ft_bzero(var_name, 100);
	state->i++;
	while (input[state->i]
		&& (ft_isalnum(input[state->i]) || input[state->i] == '_'))
	{
		var_name[var_len++] = input[state->i];
		state->i++;
	}
	var_name[var_len] = '\0';
	var_value = get_env_value(var_name, state->data->env);
	if (var_value)
	{
		ft_strcpy(&state->expanded[state->j], var_value);
		state->j += ft_strlen(var_value);
	}
	free(var_value);
	return (state->i);
}
