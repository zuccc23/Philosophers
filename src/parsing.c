#include "../include/philo.h"

// 		3		300			250			150				6	 
// n° philo   time die  time eat   time sleep    (amount of eat)

//parses the input
//returns 1 if error, 0 if not
int	parser(int ac, char **av, t_data *data)
{
	int		i;

	i = 1;
	if (ac > 6 || ac < 5)
		return (TOO_FEW_ARGS);
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10)
			return (TOO_LONG);
		if (ft_is_number(av[i]) == 0)
			return (NON_NUMERIC);
		i++;
	}
	if (get_args(av, data) != 0)
		return (NUMBER_TOO_SMALL);
	return (0);
}

int	get_args(char **av, t_data *data)
{
	data->num_philosophers = ft_atoll(av[1]);
	if (data->num_philosophers < 1)
		return (NUMBER_TOO_SMALL);
	data->time_to_die = ft_atoll(av[2]);
	if (data->time_to_die < 1)
		return (NUMBER_TOO_SMALL);
	data->time_to_eat = ft_atoll(av[3]);
	if (data->time_to_eat < 1)
		return (NUMBER_TOO_SMALL);
	data->time_to_sleep = ft_atoll(av[4]);
	if (data->time_to_sleep < 1)
		return (NUMBER_TOO_SMALL);
	if (av[5])
	{
		data->must_eat_count = ft_atoll(av[5]);
		if (data->num_philosophers < 1)
			return (NUMBER_TOO_SMALL);
	}
	return (0);
}
