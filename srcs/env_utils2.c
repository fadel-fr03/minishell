#include "../incs/minishell.h"

t_env	*init_env_list(char **envp)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		if (valid_env(envp[i]) == 1)
		{
			if (!find_and_update_env(env_list, envp[i]))
				add_env(envp[i], &env_list);
		}
		i++;
	}
	return (env_list);
}

void	printer(char *str, int j)
{
	if (j > 0 && str[j - 1] == '=')
	{
		printf("\"");
		while (str[j])
			printf("%c", str[j++]);
		printf("\"");
	}
	printf("\n");
}

int	found_in_env(char *arg, t_env *env)
{
	char	env_name1[1024];
	char	env_name2[1024];

	get_env_name(env_name1, arg);
	while (env)
	{
		get_env_name(env_name2, env->value);
		if (ft_strcmp(env_name2, env_name1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
