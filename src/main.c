#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	int			i = 0;

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

	//TEST PRINTS
	printf("philos: %d\n", data.num_philo);
	printf("death: %d\n", data.time_to_die);
	printf("eat: %d\n", data.time_to_eat);
	printf("sleep: %d\n", data.time_to_sleep);

	//INIT FORKS & PHILOS 
	init_mutexes(&data);
	init_philos(&data);
	data.start_time = get_current_time();

	// usleep(500 * 1000);
	// data.philos[0].last_meal_time = get_current_time();
	// usleep(300 * 1000);
	// printf("%ld\n", time_since_meal(data.philos[0].last_meal_time));

	//ROUTINE
	while (i < data.num_philo)
	{
		pthread_create(&data.threads[i], NULL, philo_routine, &data.philos[i]);
		i++;
	}

	//CHECK DEATH
	check_death(&data);
	i = 0;
	while (i < data.num_philo)
	{
		pthread_join(data.threads[i], NULL);
		i++;
	}

	//FREE STUFF
	// destroy_mutexes(&data);
	return (0);
}

void	check_death(t_data *data)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			// pthread_mutex_lock(&data->philos[i].meal_time);
			if (time_since_meal(data->philos[i].last_meal_time) > data->time_to_die && data->philos[i].last_meal_time != 0)
			{
				print_state(&data->philos[i], DIE);
				printf("%ld\n", time_since_meal(data->philos[i].last_meal_time));
				pthread_mutex_lock(&data->death_mutex);
				data->simulation_over = 1;
				pthread_mutex_unlock(&data->death_mutex);
				// pthread_mutex_unlock(&data->philos[i].meal_time);
				return ;
			}
			i++;
		}
	}
}

			