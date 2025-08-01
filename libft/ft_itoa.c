#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int	len;

	if (nbr <= 0)
	{
		len = 1;
	}
	else
	{
		len = 0;
	}
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill_str(int i, int n, char *str)
{
	if (n == 0)
	{
		str[i] = '0';
	}
	while (i >= 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
		if (n == 0)
			break ;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		i;

	len = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	i = len - 1;
	ft_fill_str(i, n, str);
	return (str);
}
