#include "../libft.h"

int	ft_unsigned_len(unsigned int number)
{
	int	len;

	len = 0;
	if (number == 0)
	{
		return (1);
	}
	while (number != 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_fd_unsigned(unsigned int n, int fd)
{
	char	c;

	if (n / 10)
	{
		ft_putnbr_fd_unsigned(n / 10, fd);
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

int	ft_print_unsigned(unsigned int number, int fd)
{
	ft_putnbr_fd_unsigned(number, fd);
	return (ft_unsigned_len(number));
}
