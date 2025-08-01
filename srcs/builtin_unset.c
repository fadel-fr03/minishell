#include "../incs/minishell.h"

/*	Computes the length of the environment variable
	name (up to but not including the = sign)	*/
static int	env_len(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

/*	Free the node containing the environment
	variable to unset (delete).	*/
static void	free_node(t_data *data, t_env *node)
{
	t_env	*prev;

	prev = NULL;
	if (data->env == node)
		data->env = node->next;
	else
	{
		prev = data->env;
		while (prev && prev->next != node)
			prev = prev->next;
		if (prev)
			prev->next = node->next;
	}
	free(node->value);
	free(node);
}

static int	check_unset(char **args)
{
	if (args[0] && args[1] && args[1][0]
			&& args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	return (0);
}

/*	The function to call if the user unsets an environment
	variable(s) (removes it from the list)	*/
int	builtin_unset(char **args, t_data *data)
{
	t_env	*node;
	int		i;
	int		status;

	if (!args || !data)
		return (1);
	status = check_unset(args);
	i = 1;
	while (args[i] && status != 2)
	{
		node = data->env;
		while (node)
		{
			if (!ft_strncmp(args[i], node->value, env_len(node->value))
				&& env_len(node->value) == (int)ft_strlen(args[i]))
			{
				free_node(data, node);
				break ;
			}
			node = node->next;
		}
		i++;
	}
	return (status);
}
