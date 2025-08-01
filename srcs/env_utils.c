#include "../incs/minishell.h"

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
	new_node->exported = true;
	return (new_node);
}

int	add_env(char *str, t_env **env)
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

void	get_env_name(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str2 || !str1)
		return ;
	while (str2[i] && str2[i] != '=')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

int	find_and_update_env(t_env *env, char *str)
{
	char	name[1024];
	char	temp[1024];
	int		name_len;

	if (!env)
		return (0);
	get_env_name(name, str);
	name_len = ft_strlen(name);
	while (env)
	{
		get_env_name(temp, env->value);
		if (!ft_strncmp(name, temp, name_len) && temp[name_len] == '\0')
		{
			free(env->value);
			env->value = ft_strdup(str);
			env->exported = true;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	valid_env(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				return (70);
			else
				return (-1);
		}
		i++;
	}
	if (str[i] != '=')
		return (66);
	return (1);
}
