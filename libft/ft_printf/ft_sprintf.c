#include "../libft.h"

int	sprintf_int_to_str(char *str, int num)
{
	int	len;
	int	divisor;

	len = 0;
	if (num < 0)
	{
		str[len++] = '-';
		num = -num;
	}
	if (num == 0)
	{
		str[len++] = '0';
	}
	else
	{
		divisor = get_divisor(num);
		len += convert_number_to_str(str + len, num, divisor);
	}
	return (len);
}

int	sprintf_str_to_str(char *str, const char *arg_str)
{
	int	len;

	len = 0;
	while (arg_str[len] != '\0')
	{
		str[len] = arg_str[len];
		len++;
	}
	return (len);
}

int	handle_format_to_str(char *str, char format, va_list args)
{
	int			num;
	const char	*arg_str;

	if (format == 'd')
	{
		num = va_arg(args, int);
		return (sprintf_int_to_str(str, num));
	}
	else if (format == 's')
	{
		arg_str = va_arg(args, const char *);
		return (sprintf_str_to_str(str, arg_str));
	}
	return (0);
}

int	handle_regular_char_to_str(char *str, char c)
{
	*str = c;
	return (1);
}

int	ft_sprintf(char *str, const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		total_length;

	i = 0;
	total_length = 0;
	if (!fmt || !str)
		return (-1);
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			total_length += handle_format_to_str(&str[total_length], fmt[i],
					args);
		}
		else
			total_length += handle_regular_char_to_str(&str[total_length],
					fmt[i]);
		i++;
	}
	str[total_length] = '\0';
	va_end(args);
	return (total_length);
}
