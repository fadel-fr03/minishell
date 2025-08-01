#include "../libft.h"

int	ft_print_string(char *str, int fd)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", fd);
		return (ft_strlen("(null)"));
	}
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}
