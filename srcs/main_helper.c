#include "../incs/minishell.h"

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*temp;

	temp = get_env_value("PS1", env);
	if (!temp)
	{
		prompt = ft_strdup("minishell$ ");
	}
	else
	{
		prompt = ft_strdup(temp);
	}
	return (prompt);
}

char	*read_input(t_env *env, t_data *data)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt(env);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history_entry(data, input);
	return (input);
}

int	handle_input(char *input, t_data *data)
{
	t_token		*tokens;
	t_token		*tokens_head;
	t_ast_node	*ast;

	tokens = tokenize(input, data);
	if (!tokens || data->exit_parsing != 0)
		return (free(input), free_tokens(tokens), data->exit_status = 2, 1);
	expand_tokens(&tokens, data);
	remove_leading_empty_tokens(&tokens);
	tokens_head = tokens;
	ast = parse_pipeline(&tokens, data);
	if (!ast || data->exit_parsing != 0)
		return (free(input), free_tokens(tokens), free(ast),
			data->exit_status = data->exit_parsing, 1);
	data->tokens = tokens;
	data->exit_status = execute_ast(ast, data->env, data);
	g_signal_atomic = 0;
	free_ast(ast);
	free_tokens(tokens_head);
	free(input);
	return (0);
}

int	is_empty(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	process_input(t_data *data)
{
	char	*input;

	input = read_input(data->env, data);
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	if (g_signal_atomic)
	{
		data->exit_status = g_signal_atomic;
		g_signal_atomic = 0;
	}
	if (!is_empty(input) && handle_input(input, data))
		return (0);
	else if(is_empty(input) && input)
		free(input);
	return (0);
}
