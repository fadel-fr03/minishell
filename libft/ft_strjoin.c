#include "libft.h"

static int	ft_lenstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_lenstr((char *)s1) + ft_lenstr((char *)s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - ft_lenstr((char *)s1)] != '\0')
	{
		str[i] = s2[i - ft_lenstr((char *)s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}
