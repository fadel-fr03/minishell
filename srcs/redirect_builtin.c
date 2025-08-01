#include "../incs/minishell.h"

// Checks if the command is a built-in
int	is_builtin(t_ast_node *node)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	if (ft_strcmp(node->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "exit") == 0)
		return (1);
	if (ft_strcmp(node->argv[0], "history") == 0)
		return (1);
	return (0);
}

// Checks if the current command is part of a pipe
int	has_pipe(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

// Executes the built-in command
int	execute_builtin(t_ast_node *node, t_env *env, t_data *data)
{
	if (ft_strcmp(node->argv[0], "cd") == 0)
		return (builtin_cd(node->argv, data));
	if (ft_strcmp(node->argv[0], "env") == 0)
		return (builtin_env(env));
	if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (builtin_pwd(node->argv));
	if (ft_strcmp(node->argv[0], "echo") == 0)
		return (builtin_echo(node->argv));
	if (ft_strcmp(node->argv[0], "export") == 0)
		return (builtin_export(node->argv, data));
	if (ft_strcmp(node->argv[0], "unset") == 0)
		return (builtin_unset(node->argv, data));
	if (ft_strcmp(node->argv[0], "history") == 0)
		return (builtin_history(node->argv, data));
	if (ft_strcmp(node->argv[0], "exit") == 0)
	{
		if (!has_pipe(data))
			builtin_exit(node->argv, data);
		else
			silent_builtin_exit(node->argv, data);
		return (data->exit_status);
	}
	return (-1);
}
