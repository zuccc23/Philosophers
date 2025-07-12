/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:45:06 by dahmane           #+#    #+#             */
/*   Updated: 2025/07/12 14:18:20 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data		data;

	init_data(&data);
	data.er_code = parser(ac, av, &data);
	if (data.er_code != 0)
		return (print_err(data.er_code));
	if (check_single_philo(data) == 1)
		return (0);
	allocate_data(&data);
	init_mut_and_philos(&data);
	threads_loop(&data);
	check_end(&data);
	join_loop(&data);
	end_program(&data);
	return (0);
}

int	check_single_philo(t_data data)
{
	if (data.num_philo == 1)
	{
		printf("{0} philo[0] has taken a fork\n");
		printf("\033[0;31m{%d} philo[0] died\033[0m\n", data.time_to_die);
		return (1);
	}
	return (0);
}

void	end_program(t_data	*data)
{
	destroy_mutexes(data);
	free(data->philos);
	free(data->threads);
}

void	threads_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&data->threads[i], NULL, philo_routine, \
		&data->philos[i]);
		i++;
	}
}

void	join_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
