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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	int		length;

	i = 0;
	if (!s || (*f) == NULL)
		return (NULL);
	length = ft_lenstr((char *)s);
	str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	while (i < length)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
