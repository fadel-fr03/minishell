#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}
