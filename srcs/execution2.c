#include "../incs/minishell.h"

int	handle_redirection_node(t_ast_node *node, int *in_fd,
								int *out_fd, t_data *data)
{
	int	fd;

	fd = open_redirection_fd(node, data);
	if (fd == -1)
	{
		perror(node->argv[0]);
		return (1);
	}
	if (node->type == NODE_REDIRECT_IN || node->type == NODE_HEREDOC)
	{
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
		*in_fd = fd;
	}
	else
	{
		if (*out_fd != STDOUT_FILENO)
			close(*out_fd);
		*out_fd = fd;
	}
	return (0);
}

int	process_redirections(t_ast_node *node, int *in_fd,
							int *out_fd, t_data *data)
{
	int	ret;

	if (!node)
		return (0);
	ret = process_redirections(node->left, in_fd, out_fd, data);
	if (ret != 0)
		return (ret);
	if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC)
		return (handle_redirection_node(node, in_fd, out_fd, data));
	return (0);
}

t_ast_node	*get_command_node(t_ast_node *node)
{
	while (node && node->type != NODE_COMMAND)
		node = node->left;
	return (node);
}

int	command_not_found(t_ast_node *cmd_node)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd_node->argv[0], 2);
	return (127);
}

int	handle_execve_error(char *full_path, char **new_envp)
{
	if (errno == EACCES)
	{
		perror("minishell: Permission denied");
		free(full_path);
		free_envp_array(new_envp);
		return (126);
	}
	perror("minishell: Permission Denied");
	free(full_path);
	free_envp_array(new_envp);
	return (127);
}
