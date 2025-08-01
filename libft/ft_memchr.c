#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		uc;
	size_t				i;

	i = 0;
	uc = (unsigned char)c;
	p = (const unsigned char *)s;
	while (i < n)
	{
		if (p[i] == uc)
		{
			return ((void *)(p + i));
		}
		i++;
	}
	return (NULL);
}
