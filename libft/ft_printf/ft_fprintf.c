#include "../libft.h"

int	handle_format_specifier(int fd, char format, va_list args)
{
	if (format == '\0')
		return (0);
	return (ft_check_format(args, format, fd));
}

int	handle_regular_char(int fd, char c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		total_length;

	i = 0;
	total_length = 0;
	if (!fmt)
		return (-1);
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			total_length += handle_format_specifier(fd, fmt[i], args);
		}
		else
			total_length += handle_regular_char(fd, fmt[i]);
		i++;
	}
	va_end(args);
	return (total_length);
}
