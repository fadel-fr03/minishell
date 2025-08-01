#include "../incs/minishell.h"

static int	is_valid_flag(char *flag)
{
	int	i;

	if (!flag || flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (args[i] && is_valid_flag(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
