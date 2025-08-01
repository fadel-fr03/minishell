#include "../incs/minishell.h"

/*	Free the environment variables list
	in case of an error.	*/
int	free_env(t_env *env, t_env *node)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		if (env->value)
			free(env->value);
		free(env);
		env = temp;
	}
	if (node)
		free(node);
	return (1);
}

/*	Initialize the env lists.	*/
/* Initialize the env lists. */
static int	init_env(t_env **env, char **envp)
{
	t_env	*temp;
	int		i;
	t_env	*new_node;

	temp = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (free_env(*env, NULL));
		new_node->value = ft_strdup(envp[i]);
		if (!new_node->value)
			return (free_env(*env, new_node));
		new_node->next = NULL;
		new_node->exported = true;
		if (!*env)
			*env = new_node;
		else
			temp->next = new_node;
		temp = new_node;
		i++;
	}
	return (0);
}

/*	Initialize all values in the data structure.	*/
int	init_data(t_data *data, char **envp)
{
	data->exit = 0;
	data->exit_status = 0;
	data->exit_parsing = 0;
	data->env = NULL;
	data->tokens = NULL;
	data->history_head = NULL;
	data->history_tail = NULL;
	if (!envp || !envp[0])
		return (1);
	if (init_env(&data->env, envp))
		return (1);
	increment_shlvl(data->env);
	return (0);
}

void	free_history(t_data *data)
{
	t_history_node	*current;
	t_history_node	*tmp;

	if (!data)
		return ;
	current = data->history_head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->cmd);
		free(tmp);
	}
	data->history_head = NULL;
	data->history_tail = NULL;
}
