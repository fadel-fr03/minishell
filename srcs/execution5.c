#include "../incs/minishell.h"

static void	execute_left_child(t_pipe_params *params)
{
	dup2(params->pipefd[1], STDOUT_FILENO);
	close(params->pipefd[0]);
	close(params->pipefd[1]);
	exit(execute_ast(params->node->left, params->env, params->data));
}

static void	execute_right_child(t_pipe_params *params)
{
	dup2(params->pipefd[0], STDIN_FILENO);
	close(params->pipefd[1]);
	close(params->pipefd[0]);
	exit(execute_ast(params->node->right, params->env, params->data));
}

/* Helper function to wait for child processes */
static int	wait_for_children(pid_t pid_left, pid_t pid_right)
{
	int	status_left;
	int	status_right;

	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	else if (WIFSIGNALED(status_right))
		return (128 + WTERMSIG(status_right));
	return (1);
}

/* Helper function to initialize pipe parameters */
static void	init_pipe_params(t_pipe_params *params, t_ast_node *node,
				t_env *env, t_data *data)
{
	params->node = node;
	params->env = env;
	params->data = data;
}

/* Main function refactored to be less than 25 lines */
int	execute_pipe(t_ast_node *node, t_env *env, t_data *data)
{
	t_pipe_params	params;
	pid_t			pid_left;
	pid_t			pid_right;

	init_pipe_params(&params, node, env, data);
	if (pipe(params.pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid_left = fork();
	if (pid_left == 0)
		execute_left_child(&params);
	pid_right = fork();
	if (pid_right == 0)
		execute_right_child(&params);
	close(params.pipefd[0]);
	close(params.pipefd[1]);
	return (wait_for_children(pid_left, pid_right));
}
