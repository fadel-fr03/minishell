#include "../libft.h"

int	ft_print_hex(unsigned long n, int fd)
{
	int	count;

	count = 0;
	if (n / 16 > 0)
		count += ft_print_hex(n / 16, fd);
	n = n % 16;
	if (n < 10)
		count += ft_print_char(n + '0', fd);
	else
		count += ft_print_char(n - 10 + 'a', fd);
	return (count);
}

int	ft_print_pointer(void *p, int fd)
{
	unsigned long	address;
	int				count;

	address = (unsigned long)p;
	if (p == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (ft_strlen("(nil)"));
	}
	count = 0;
	count += ft_print_char('0', fd);
	count += ft_print_char('x', fd);
	count += ft_print_hex(address, fd);
	return (count);
}
