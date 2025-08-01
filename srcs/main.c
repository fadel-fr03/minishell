#include "../incs/minishell.h"

volatile sig_atomic_t	g_signal_atomic;

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_atomic = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main_loop(t_data *data)
{
	while (data->exit == 0)
	{
		if (process_input(data))
			break ;
	}
	free_env(data->env, NULL);
	free_history(data);
	return (data->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	init_data(&data, envp);
	return (main_loop(&data));
}
