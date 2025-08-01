#include "../libft.h"

int	ft_number_len(int number)
{
	int	len;

	len = 0;
	if (number <= 0)
		len++;
	while (number != 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

int	ft_print_decimal(int number, int fd)
{
	ft_putnbr_fd(number, fd);
	return (ft_number_len(number));
}
