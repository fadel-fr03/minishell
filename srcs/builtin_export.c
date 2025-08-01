#include "../incs/minishell.h"

static int	found_error(char *arg, int pos)
{
	int	i;

	if (!ft_strcmp(arg, "--") && pos == 1)
		return (0);
	if (arg[0] == '-' && arg[1] && pos == 1)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(arg[0], 2);
		ft_putchar_fd(arg[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: export: `", 2);
	i = 0;
	while (arg[i])
	{
		ft_putchar_fd(arg[i], 2);
		i++;
	}
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static t_env	*create_node(char *str)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(str);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->exported = false;
	return (new_node);
}

static int	add_non_exported(char *str, t_env **env)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_node(str);
	if (!new_node)
		return (1);
	if (!*env)
	{
		*env = new_node;
		return (0);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (0);
}

static int	check_export(int ret, t_env *env, char *arg)
{
	char	*plus;

	if (ret <= 0)
		return (1);
	else if (ret == 66)
	{
		if (!found_in_env(arg, env))
			add_non_exported(arg, &env);
		return (1);
	}
	else if (ret == 70)
	{
		plus = remove_plus_char(arg);
		if (!found_in_env(plus, env))
			add_env(plus, &env);
		else if (found_in_env(plus, env) && is_not_exported(plus, env))
			replace_env(plus, &env);
		else
			add_concatenated_env(plus, &env);
		free(plus);
		return (1);
	}
	else
		return (find_and_update_env(env, arg));
}

int	builtin_export(char **args, t_data *data)
{
	int	ret;
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		print_sorted_env(data->env);
		return (0);
	}
	i = 1;
	while (args[i] && status != 2)
	{
		ret = valid_env(args[i]);
		if (ret <= 0)
			status = found_error(args[i], i);
		else if (check_export(ret, data->env, args[i]) == 0)
			add_env(args[i], &(data->env));
		i++;
	}
	return (status);
}
