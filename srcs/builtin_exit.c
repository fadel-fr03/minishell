#include "../incs/minishell.h"

static int	calc_status(long long n)
{
	if (n < 0 || n > 255)
	{
		n = n % 256;
		if (n < 0)
			n += 256;
	}
	return ((int)n);
}

static int	check_sign(char **arg)
{
	int	sign;

	sign = 1;
	if (**arg == '-' || **arg == '+')
	{
		if (**arg == '-')
			sign = -1;
		(*arg)++;
	}
	return (sign);
}

static int	check_overflow(char *arg)
{
	long long	result;
	int			sign;
	size_t		len;

	while (*arg && ft_isspace(*arg))
		arg++;
	sign = check_sign(&arg);
	len = ft_strlen(&(*arg));
	if (len == 0 || len > 19)
		return (1);
	result = 0;
	while (*arg)
	{
		result = result * 10 + (*arg - '0');
		arg++;
	}
	if (sign == -1 && (unsigned long long)result > 9223372036854775808ULL)
		return (1);
	if (sign == 1 && (unsigned long long)result > 9223372036854775807ULL)
		return (1);
	return (0);
}

void	silent_builtin_exit(char **args, t_data *data)
{
	int	status;

	data->exit = 1;
	if (args[1] && (!str_num(args[1]) || check_overflow(args[1])))
		data->exit_status = 2;
	else if (args[1] && args[2])
	{
		data->exit = 0;
		data->exit_status = 1;
	}
	else if (args[1])
	{
		status = ft_atoi(args[1]);
		data->exit_status = calc_status((long long)status);
	}
	else
		data->exit_status = 0;
}

void	builtin_exit(char **args, t_data *data)
{
	int	status;

	data->exit = 1;
	ft_putendl_fd("exit", 2);
	if (args[1] && (!str_num(args[1]) || check_overflow(args[1])))
	{
		data->exit_status = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (args[1] && args[2])
	{
		data->exit = 0;
		data->exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args[1])
	{
		status = ft_atoi(args[1]);
		data->exit_status = calc_status((long long)status);
	}
	else
		data->exit_status = 0;
}
