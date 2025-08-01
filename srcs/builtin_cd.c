#include "../incs/minishell.h"

/*	Print a message if we have more than one
	argument to cd or an error occurred
	trying to change the current directory	*/
static void	error_found(char **args, int *ret)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (args[1][0] == '-')
	{
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putendl_fd(": invalid option", 2);
		*ret = 2;
		return ;
	}
	else if (args[2])
		ft_putendl_fd("too many arguments", 2);
	else
		perror(args[1]);
	*ret = 1;
}

/*	Get the value stored in OLDPWD or HOME
	according to cd input	*/
static char	*get_path(t_env *env, char *path)
{
	int		len;

	len = ft_strlen(path);
	while (env)
	{
		if (ft_strncmp(env->value, path, len) == 0
			&& env->value[len] == '=')
			return (ft_strdup(env->value + len + 1));
		env = env->next;
	}
	return (NULL);
}

/*	Update the value of the OLDPWD environment variable	*/
static int	update_oldpwd(t_env **env)
{
	char	cwd[1024];
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (1);
	if (!find_and_update_env(*env, oldpwd))
		add_env(oldpwd, env);
	free(oldpwd);
	return (0);
}

/*	Change the current directory to the value set
	in HOME or OLDPWD environment variables	*/
static int	go(t_env *env, char *var)
{
	int		ret;
	char	*path;

	path = get_path(env, var);
	ret = 0;
	if (!path)
	{
		ft_putstr_fd("minishell : cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	if (ft_strcmp("OLDPWD", var) == 0)
		ft_putendl_fd(path, 1);
	update_oldpwd(&env);
	if (path[0] != '\0')
		ret = chdir(path);
	free(path);
	return (ret);
}

/*	The cd function to be called	*/
int	builtin_cd(char **args, t_data *data)
{
	int	ret;

	if (!args[1] || (args[1] && !ft_strcmp(args[1], "--")))
		ret = go(data->env, "HOME");
	else if (!ft_strncmp(args[1], "-", 1) && ft_strlen(args[1]) == 1)
		ret = go(data->env, "OLDPWD");
	else if (args[1] && args[1][0] == '-')
		error_found(args, &ret);
	else if (args[1] && args[2])
		error_found(args, &ret);
	else
	{
		if (!is_directory(args[1]))
		{
			ret = chdir(args[1]);
			error_found(args, &ret);
		}
		else
		{
			update_oldpwd(&(data->env));
			ret = chdir(args[1]);
		}
	}
	update_pwd(&(data->env));
	return (ret);
}
