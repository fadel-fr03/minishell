#include "../libft.h"

int	ft_check_format(va_list args, const char format, int fd)
{
	int	len;

	len = 0;
	if (format == '%')
		len = ft_print_percent(fd);
	else if (format == 'c')
		len = ft_print_char(va_arg(args, int), fd);
	else if (format == 'd' || format == 'i')
		len = ft_print_decimal(va_arg(args, int), fd);
	else if (format == 'u')
		len = ft_print_unsigned(va_arg(args, unsigned int), fd);
	else if (format == 's')
		len = ft_print_string(va_arg(args, char *), fd);
	else if (format == 'p')
		len = ft_print_pointer(va_arg(args, void *), fd);
	else if (format == 'x')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef",
				fd);
	else if (format == 'X')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF",
				fd);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		total_length;

	i = 0;
	total_length = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			total_length += ft_check_format(args, fmt[i + 1], STDOUT_FILENO);
			i++;
		}
		else
		{
			ft_putchar_fd(fmt[i], 1);
			total_length++;
		}
		i++;
	}
	va_end(args);
	return (total_length);
}
