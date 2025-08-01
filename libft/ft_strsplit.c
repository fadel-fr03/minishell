#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static char	*ft_get_word(char *word, char c)
{
	char	*start;

	start = word;
	while (*word && *word != c)
		word++;
	*word = '\0';
	return (ft_strdup(start));
}

static void	ft_free_words(char **words, size_t i)
{
	while (i--)
	{
		free(words[i]);
	}
	free(*words);
}

static char	**ft_get_words(char *s, char c, size_t words_count)
{
	char	**words;
	char	*word;
	size_t	i;

	i = 0;
	words = (char **)ft_calloc(words_count + 1, sizeof(char *));
	while (i < words_count)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			word = ft_get_word(s, c);
			if (!(word))
			{
				ft_free_words(words, i);
				return (NULL);
			}
			words[i++] = word;
			s += (ft_strlen(word) + 1);
		}
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	char	*line;

	line = ft_strdup((char *)s);
	if (!s || !(line))
		return (NULL);
	words = ft_get_words(line, c, ft_count_words(line, c));
	free(line);
	return (words);
}
