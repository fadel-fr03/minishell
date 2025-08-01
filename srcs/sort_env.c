#include "../incs/minishell.h"

static void	free_2d_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/*	Function to sort a string tab	*/
static void	sort(char **str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*	Get the total length of the environment
	variables combined.	*/
static int	len_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value != NULL)
			i += ft_strlen(env->value);
		if (env->next != NULL)
			i++;
		env = env->next;
	}
	return (i);
}

/*	Convert the values in the env list into one 
	string.	*/
static char	*env_to_str(t_env *env)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * (len_env(env) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			j = 0;
			while (env->value[j])
				str[i++] = env->value[j++];
		}
		if (env->next != NULL)
			str[i++] = '\n';
		env = env->next;
	}
	str[i] = '\0';
	return (str);
}

/*	Print the values of the env list in a sorted manner	*/
void	print_sorted_env(t_env *env)
{
	int		i;
	int		j;
	char	**array;
	char	*str;

	if (!env || (!env->next && !env->value))
		return ;
	str = env_to_str(env);
	array = ft_split(str, '\n');
	sort(array);
	i = 0;
	while (array[i])
	{
		j = 0;
		printf("declare -x ");
		while (array[i][j] && (j == 0 || array[i][j - 1] != '='))
			printf("%c", array[i][j++]);
		printer(array[i], j);
		i++;
	}
	free_2d_array(array);
	free(str);
}
