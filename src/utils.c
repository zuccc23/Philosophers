#include "../include/philo.h"

//returns 1 if its a number
//0 if not
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// check if a string only has numbers
// returns 1 if its a number, and 0 if it has other characters
int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long	ft_atoll(const char *str)
{
	long	i;
	long	sign;
	long	n;

	i = 0;
	sign = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0')
	{
		n = (n * 10) + str[i] - '0';
		i++;
	}
	if (sign == 1)
		n = n * (-1);
	return (n);
}

// prints a string on STDERR
void	ft_putsterr(char *s)
{
	while (*s)
	{
		write(STDERR_FILENO, &*s, 1);
		s++;
	}
}
