#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	cc;

	str = (char *)s;
	cc = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == cc)
		{
			str = (char *)&s[i];
			return (str);
		}
		i--;
	}
	return (NULL);
}
