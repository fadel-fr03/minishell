#include "../incs/minishell.h"

/*	Check if the value in SHLVL is valid	*/
static int	check_lvl(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*	Function that returns the value of an environment
	variable given as a string	*/
char	*get_env_value(char *str, t_env *env)
{
	char	*env_value;
	char	env_name[1024];
	int		i;

	env_value = NULL;
	while (env)
	{
		get_env_name(env_name, env->value);
		if (!ft_strcmp(str, env_name))
		{
			i = 0;
			while (env->value[i] && env->value[i] != '=')
				i++;
			if (env->value[i] == '\0')
				return (NULL);
			i++;
			env_value = ft_strdup(&(env->value[i]));
			if (!env_value)
				return (NULL);
			return (env_value);
		}
		env = env->next;
	}
	return (NULL);
}

/*	Convert the value in SHLVL to an integer	*/
static int	get_lvl_number(char *str)
{
	int	lvl;

	if (!check_lvl(str))
		return (-300);
	lvl = ft_atoi(str);
	return (lvl);
}

/*	Increments the value of SHLVL in a new subshell	*/
void	increment_shlvl(t_env *env)
{
	char	*shlvl_str;
	char	*shlvl_join;
	int		lvl;

	shlvl_str = get_env_value("SHLVL", env);
	if (!shlvl_str || !shlvl_str[0])
	{
		free(shlvl_str);
		return ;
	}
	lvl = get_lvl_number(shlvl_str) + 1;
	free(shlvl_str);
	if (lvl == -299)
		return ;
	shlvl_str = ft_itoa(lvl);
	shlvl_join = ft_strjoin("SHLVL=", shlvl_str);
	if (!shlvl_join)
	{
		free(shlvl_str);
		return ;
	}
	find_and_update_env(env, shlvl_join);
	free(shlvl_str);
	free(shlvl_join);
}
