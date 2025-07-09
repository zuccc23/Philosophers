#include "../include/philo.h"

//destroy and free the array of forks
void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}