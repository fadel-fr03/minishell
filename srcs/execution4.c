#include "../incs/minishell.h"

static void	handle_child_process(t_exec_params *params)
{
	if (params->in_fd != STDIN_FILENO)
	{
		dup2(params->in_fd, STDIN_FILENO);
		close(params->in_fd);
	}
	if (params->out_fd != STDOUT_FILENO)
	{
		dup2(params->out_fd, STDOUT_FILENO);
		close(params->out_fd);
	}
	if (is_builtin(params->node))
		exit(execute_builtin(params->node, params->env, params->data));
	else
		execute_command_node(params->node, params->env, params->data);
}

static int	handle_parent_process(pid_t pid, int in_fd, int out_fd)
{
	int	status;

	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_simple_command(t_ast_node *node, t_env *env, t_data *data)
{
	t_exec_params	params;
	int				ret;
	pid_t			pid;

	params.node = node;
	params.env = env;
	params.data = data;
	params.in_fd = STDIN_FILENO;
	params.out_fd = STDOUT_FILENO;
	ret = process_redirections(node, &params.in_fd, &params.out_fd, data);
	if (ret != 0)
		return (ret);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		handle_child_process(&params);
	else if (pid > 0)
		return (handle_parent_process(pid, params.in_fd, params.out_fd));
	return (data->exit_status);
}

static size_t	get_var_expanded_length(const char *input, size_t *i,
											t_data *data)
{
	char	var_name[100];
	char	*value;
	int		var_len;
	size_t	len;

	var_len = 0;
	while (input[*i] && (isalnum((unsigned char)input[*i])
			|| input[*i] == '_') && var_len < 99)
		var_name[var_len++] = input[(*i)++];
	var_name[var_len] = '\0';
	value = get_env_value(var_name, data->env);
	if (value)
		len = ft_strlen(value);
	else
		len = 0;
	free(value);
	return (len);
}

// Helper function to compute the expanded length of the input line.
size_t	compute_expanded_length(const char *input, t_data *data)
{
	size_t	length;
	size_t	i;

	i = 0;
	length = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			length += get_var_expanded_length(input, &i, data);
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}
