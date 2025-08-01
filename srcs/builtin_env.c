#include "../incs/minishell.h"

/*	Prints the values un the env list	*/
int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->exported == true)
			printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
