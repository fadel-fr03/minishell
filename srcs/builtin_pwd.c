#include "../incs/minishell.h"

static int	check_args(char **args)
{
	if (args[1] && !ft_strcmp(args[1], "--"))
		return (0);
	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (1);
	}
	return (0);
}

/*	Print the current working directory	*/
int	builtin_pwd(char **args)
{
	char	cwd[4096];
	int		status;

	status = 0;
	if (args[1])
		status = check_args(args);
	if (status)
		return (2);
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2);
	return (1);
}
