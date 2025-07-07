#include "../include/philo.h"

void	init_data(t_data *data)
{
	data->num_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat_count = 0;
	data->start_time = 0;
	data->simulation_over = 0;
	data->er_code = 0;
	data->forks = NULL;
	// data->print_mutex =
	//data->death_mutex =
	data->threads = NULL;
	data->philosophers = NULL;
}
