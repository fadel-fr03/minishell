#include "../incs/minishell.h"

int	execute_ast(t_ast_node *node, t_env *env, t_data *data)
{
	if (!node)
		return (0);
	if (is_builtin(node) && !has_pipe(data))
		return (execute_builtin(node, env, data));
	if (node->type == NODE_COMMAND || node->type == NODE_REDIRECT_IN
		|| node->type == NODE_REDIRECT_OUT || node->type == NODE_APPEND
		|| node->type == NODE_HEREDOC)
		return (execute_simple_command(node, env, data));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, env, data));
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Unknown node type\n");
		return (1);
	}
}

static void	setup_heredoc_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

static void	handle_heredoc_child(int *pipefd, const char *delimiter,
									t_data *data)
{
	setup_heredoc_signals(1);
	close(pipefd[0]);
	read_heredoc_lines(pipefd[1], delimiter, data);
	close(pipefd[1]);
	exit(0);
}

int	handle_heredoc(const char *delimiter, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	setup_heredoc_signals(0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	else if (pid == 0)
		handle_heredoc_child(pipefd, delimiter, data);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return (-1);
	}
	return (pipefd[0]);
}
