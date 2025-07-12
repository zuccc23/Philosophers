/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:45:45 by dahmane           #+#    #+#             */
/*   Updated: 2025/07/12 13:11:11 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//sets data values to 0 or NULL
void	init_data(t_data *data)
{
	data->num_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat_count = 0;
	data->start_time = 0;
	data->simulation_over = 0;
	data->er_code = 0;
	data->forks = NULL;
	data->threads = NULL;
	data->philos = NULL;
}

// mutex_init the fork array
void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->philos[i].meal_time, NULL);
		pthread_mutex_init(&data->philos[i].meal_count, NULL);
		i++;
	}
}

//assign the values of each philosopher
//= forks, id, etc...
void	init_philos(t_data *data)
{
	int	i;
	int	right_fork;

	i = 0;
	right_fork = 0;
	while (i < data->num_philo)
	{
		right_fork = (i + 1) % data->num_philo;
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		if (data->num_philo == 1)
			data->philos[i].right_fork = NULL;
		else
			data->philos[i].right_fork = &data->forks[right_fork];
		data->philos[i].data = data;
		i++;
	}
}

void	init_mut_and_philos(t_data *data)
{
	init_mutexes(data);
	init_philos(data);
	data->start_time = get_current_time();
}

int	allocate_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (1);
	data->threads = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->threads)
	{
		free(data->philos);
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
	{
		free(data->philos);
		free(data->threads);
		return (1);
	}
	return (0);
}
