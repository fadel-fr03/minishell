#include "../incs/minishell.h"

void	check_command_node(t_ast_node *cmd_node)
{
	if (!cmd_node)
	{
		ft_fprintf(STDERR_FILENO, "Error: Command not found\n");
		exit(1);
	}
}

void	check_if_directory(t_ast_node *cmd_node)
{
	if (is_directory(cmd_node->argv[0]) && ft_strncmp(cmd_node->argv[0], "./",
			2) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_node->argv[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
}

int	execute_external_command(t_ast_node *cmd_node, t_env *env)
{
	char	*full_path;
	char	**new_envp;

	full_path = find_full_path(cmd_node->argv[0], env);
	if (full_path)
	{
		new_envp = envp_to_array(env);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(full_path, cmd_node->argv, new_envp);
		return (handle_execve_error(full_path, new_envp));
	}
	else
		return (command_not_found(cmd_node));
}

void	execute_command_node(t_ast_node *node, t_env *env, t_data *data)
{
	t_ast_node	*cmd_node;

	cmd_node = get_command_node(node);
	check_command_node(cmd_node);
	check_if_directory(cmd_node);
	if (is_builtin(node))
		exit(execute_builtin(node, env, data));
	exit(execute_external_command(cmd_node, env));
}
