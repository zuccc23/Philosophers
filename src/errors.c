#include "../include/philo.h"

//prints an error message depending on the error code
int	print_err(int er_code)
{
	if (er_code == NON_NUMERIC)
		ft_putsterr("Non numeric characters entered.\n");
	if (er_code == TOO_LONG)
		ft_putsterr("Some of the arguments are too long.\n");
	if (er_code == NUMBER_TOO_SMALL)
		ft_putsterr("All arguments must be positive integers.\n");
	if (er_code == TOO_FEW_ARGS)
		ft_putsterr("Not enough arguments.\n");
	return (1);
}