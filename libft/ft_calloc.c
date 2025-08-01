#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	total_size;

	if (size != 0 && nmemb > 2147483647 / size)
		return (NULL);
	total_size = nmemb * size;
	ret = malloc(total_size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, total_size);
	return (ret);
}
