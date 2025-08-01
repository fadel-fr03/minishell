#include "../incs/minishell.h"

/* Handle SIGINT inside heredoc */
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static void	process_variable(char **inp, char *out,
								size_t *out_idx, t_data *data)
{
	char	var_name[100];
	char	*value;
	size_t	value_len;
	int		var_len;

	var_len = 0;
	while (**inp && (isalnum((unsigned char)**inp)
			|| **inp == '_') && var_len < 99)
		var_name[var_len++] = *(*inp)++;
	var_name[var_len] = '\0';
	value = get_env_value(var_name, data->env);
	if (value)
	{
		value_len = ft_strlen(value);
		ft_memcpy(out + *out_idx, value, value_len);
		*out_idx += value_len;
		free(value);
	}
}

char	*expand_line(char *input, t_data *data)
{
	size_t		final_length;
	size_t		out_idx;
	char		*expanded;
	char		*p;

	final_length = compute_expanded_length(input, data);
	expanded = malloc(final_length + 1);
	if (!expanded)
		return (NULL);
	out_idx = 0;
	p = input;
	while (*p)
	{
		if (*p == '$')
		{
			p++;
			process_variable(&p, expanded, &out_idx, data);
		}
		else
			expanded[out_idx++] = *p++;
	}
	expanded[out_idx] = '\0';
	return (expanded);
}

static char	*get_expanded_line(const char *delimeter, t_data *data)
{
	char	*line;
	char	*expanded;
	char	*trimmed_delimiter;
	char	*trimmed_line;

	line = readline("heredoc> ");
	if (!line || !ft_strcmp(line, delimeter))
	{
		free (line);
		return (NULL);
	}
	trimmed_delimiter = ft_strtrim(delimeter, " \t");
	trimmed_line = ft_strtrim(line, " \t");
	if (!ft_strcmp(trimmed_delimiter, trimmed_line))
	{
		free(line);
		free(trimmed_delimiter);
		free(trimmed_line);
		return (NULL);
	}
	expanded = expand_line(line, data);
	free(line);
	free(trimmed_delimiter);
	free(trimmed_line);
	return (expanded);
}

int	read_heredoc_lines(int write_fd, const char *delimiter, t_data *data)
{
	char	*expanded_line;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		expanded_line = get_expanded_line(delimiter, data);
		if (!expanded_line)
		{
			break ;
		}
		write(write_fd, expanded_line, ft_strlen(expanded_line));
		write(write_fd, "\n", 1);
		free(expanded_line);
	}
	signal(SIGINT, SIG_IGN);
	return (0);
}
