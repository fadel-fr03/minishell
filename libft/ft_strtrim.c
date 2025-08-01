#include "libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

static size_t	ft_lenstr(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimmed;
	const char	*start;
	const char	*end;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_is_in_set(*start, set))
		start++;
	end = s1 + ft_lenstr(s1) - 1;
	while (end > start && ft_is_in_set(*end, set))
		end--;
	len = end - start + 1;
	trimmed = (char *)ft_calloc(len + 1, 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, len + 1);
	trimmed[len] = '\0';
	return (trimmed);
}
