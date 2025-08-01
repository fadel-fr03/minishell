#include "../incs/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*get_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->value, "PATH=", 5) == 0)
			return (env->value + 5);
		env = env->next;
	}
	return (NULL);
}

static char	*construct_full_path(const char *dir, const char *command)
{
	size_t	len;
	char	*full_path;

	len = ft_strlen(dir) + ft_strlen(command) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
	{
		perror("malloc");
		return (NULL);
	}
	snprintf(full_path, len, "%s/%s", dir, command);
	return (full_path);
}

static char	*search_directories(char **dirs, const char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = construct_full_path(dirs[i], command);
		if (!full_path)
		{
			ft_free_split(dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

char	*find_full_path(const char *command, t_env *env)
{
	char	*path_env;
	char	**dirs;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (search_directories(dirs, command));
}
