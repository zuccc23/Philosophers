#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	check;

	// INIT DATA
	init_data(&data);

	// PARSING
	data.er_code = parser(ac, av, &data);
	if (data.er_code != 0)
		return (print_err(data.er_code));

	//MALLOC DATA
	data.philos = malloc(sizeof(t_philo) * data.num_philo);
	if (!data.philos)
		return (1);
	data.threads = malloc(sizeof(pthread_t) * data.num_philo);
	if (!data.threads)
		return (1); //+free
	data.forks = malloc(sizeof(pthread_mutex_t) * data.num_philo);
	if (!data.forks)
		return (1); //+free

	//INIT FORKS & PHILOS
	init_forks(&data);
	init_philos(&data);
	data.start_time = get_start_time();

	//ROUTINE
	pthread_create(&check, NULL, check_death, &data);
	pthread_create(&data.threads[0], NULL, philo_routine, &data.philos[0]);
	pthread_create(&data.threads[1], NULL, philo_routine, &data.philos[1]);
	pthread_create(&data.threads[2], NULL, philo_routine, &data.philos[2]);
	pthread_create(&data.threads[3], NULL, philo_routine, &data.philos[3]);
	pthread_join(check, NULL);
	pthread_join(data.threads[0], NULL);
	pthread_join(data.threads[1], NULL);
	pthread_join(data.threads[2], NULL);
	pthread_join(data.threads[3], NULL);

	//FREE STUFF
	destroy_mutexes(&data);
	return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		while (i < data->num_philo)
		{
			if (data->philos[i].last_meal_time == 0)
			{
				if (get_start_time() - data->start_time > data->time_to_die)
				{
					print_state(&data->philos[i], DIE);
				}
			}
			else
			{
				if (get_start_time() - data->philos[i].last_meal_time > data->time_to_die)
				{
					print_state(&data->philos[i], DIE);
				}
			}
			i++;
		}
	}
	return (NULL);
}
