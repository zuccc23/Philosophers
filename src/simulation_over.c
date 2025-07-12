/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_over.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:46:00 by dahmane           #+#    #+#             */
/*   Updated: 2025/07/12 12:47:56 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//checks if simulation over by setting data->simulation_over to 1
void	check_end(t_data *data)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (check_death(data, i) == 1)
				return ;
			i++;
		}
		if (check_meals_eaten(data) == 1)
			return ;
	}
}

//returns 1 if a philo died, 0 if none are dead
int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].meal_time);
	if (time_since_meal(data->philos[i].last_meal_time) > \
	data->time_to_die && data->philos[i].last_meal_time != 0)
	{
		print_state(&data->philos[i], DIE);
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_time);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_time);
	return (0);
}

//returns 1 if all philos have eaten all their required meals, 0 if not
int	check_meals_eaten(t_data *data)
{
	int	i;
	int	philos_full;

	if (data->must_eat_count <= 0)
		return (0);
	i = 0;
	philos_full = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_count);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			philos_full++;
		pthread_mutex_unlock(&data->philos[i].meal_count);
		i++;
	}
	if (philos_full >= data->num_philo)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
