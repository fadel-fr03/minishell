#include "../incs/minishell.h"

static int	clear_hist(t_data *data)
{
	t_history_node	*current;
	t_history_node	*tmp;

	current = data->history_head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->cmd);
		free(tmp);
	}
	data->history_head = NULL;
	data->history_tail = NULL;
	clear_history();
	return (0);
}

int	builtin_history(char **args, t_data *data)
{
	t_history_node	*current;
	int				index;

	index = 1;
	if (!data)
		return (1);
	if (args[1] && (ft_strcmp(args[1], "-c") == 0))
		return (clear_hist(data));
	current = data->history_head;
	while (current)
	{
		printf("%d  %s\n", index, current->cmd);
		current = current->next;
		index++;
	}
	return (0);
}
