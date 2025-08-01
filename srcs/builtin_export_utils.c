#include "../incs/minishell.h"

char	*remove_plus_char(char *str)
{
	char	*plus;
	int		i;
	int		j;

	plus = (char *)malloc(ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '+')
			plus[j++] = str[i];
		i++;
	}
	plus[j] = '\0';
	return (plus);
}

static char	*get_value(char	*str)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	len = ft_strlen(&str[i]) + 1;
	result = (char *)malloc(len);
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	add_concatenated_env(char *plus, t_env **env)
{
	char	env_name_loop[1024];
	char	env_name_new[1024];
	char	*env_value_new;
	char	*final_env;

	get_env_name(env_name_new, plus);
	while (*env)
	{
		get_env_name(env_name_loop, (*env)->value);
		if (!ft_strcmp(env_name_loop, env_name_new))
		{
			env_value_new = get_value(plus);
			if (!env_value_new)
				return ;
			final_env = ft_strjoin((*env)->value, env_value_new);
			if (final_env)
			{
				free((*env)->value);
				(*env)->value = final_env;
			}
			free(env_value_new);
			return ;
		}
		(*env) = (*env)->next;
	}
}

int	is_not_exported(char *arg, t_env *env)
{
	int	i;

	while (env)
	{
		i = 0;
		while (arg[i] && env->value[i] && arg[i] == env->value[i])
			i++;
		if (arg[i] == '=' && env->value[i] == '\0')
			return (1);
		env = env->next;
	}
	return (0);
}

void	replace_env(char *value, t_env **env)
{
	char	env_name_loop[1024];
	char	env_name_new[1024];

	get_env_name(env_name_new, value);
	while (*env)
	{
		get_env_name(env_name_loop, (*env)->value);
		if (!ft_strcmp(env_name_loop, env_name_new))
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			(*env)->exported = true;
			return ;
		}
		*env = (*env)->next;
	}
}
