#include "../incs/minishell.h"

static int	is_valid_history_entry(const char *cmd)
{
	char	*trimmed_cmd;
	int		result;

	if (!cmd || *cmd == '\0')
		return (0);
	trimmed_cmd = ft_strtrim(cmd, " \t");
	if (!trimmed_cmd)
		return (0);
	result = ft_strcmp(trimmed_cmd, "history") != 0;
	free(trimmed_cmd);
	add_history(cmd);
	return (result);
}

int	add_history_entry(t_data *data, const char *cmd)
{
	t_history_node	*new_node;

	if (!is_valid_history_entry(cmd))
		return (0);
	new_node = malloc(sizeof(t_history_node));
	if (!new_node)
		return (1);
	new_node->cmd = ft_strdup(cmd);
	if (!new_node->cmd)
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL;
	if (data->history_head == NULL)
	{
		data->history_head = new_node;
		data->history_tail = new_node;
	}
	else
	{
		data->history_tail->next = new_node;
		data->history_tail = new_node;
	}
	return (0);
}
