#include "../incs/minishell.h"

/* Convert linked list environment to array */
char	**envp_to_array(t_env *env)
{
	int		count;
	t_env	*temp;
	char	**envp;
	int		i;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i++] = ft_strdup(env->value);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

/* Free allocated envp array */
void	free_envp_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

/* Open file descriptor based on redirection type */
int	open_redirection_fd(t_ast_node *node, t_data *data)
{
	int	fd;

	fd = -1;
	if (node->type == NODE_REDIRECT_IN)
		fd = open(node->argv[0], O_RDONLY);
	else if (node->type == NODE_REDIRECT_OUT)
		fd = open(node->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_APPEND)
		fd = open(node->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == NODE_HEREDOC)
		fd = handle_heredoc(node->argv[0], data);
	return (fd);
}
