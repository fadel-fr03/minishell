int	get_divisor(int num)
{
	int	divisor;

	divisor = 1;
	while (num / 10 > 0)
	{
		num /= 10;
		divisor *= 10;
	}
	return (divisor);
}

int	convert_number_to_str(char *str, int num, int divisor)
{
	int	len;

	len = 0;
	while (divisor > 0)
	{
		str[len++] = (num / divisor) + '0';
		num %= divisor;
		divisor /= 10;
	}
	return (len);
}
