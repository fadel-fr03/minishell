#include "../incs/minishell.h"

int	update_pwd(t_env **env)
{
	char	cwd[1024];
	char	*pwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	if (!find_and_update_env(*env, pwd))
		add_env(pwd, env);
	free(pwd);
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return ((((path_stat.st_mode)) & 0170000) == (0040000));
}
