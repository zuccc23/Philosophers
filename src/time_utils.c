/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:46:07 by dahmane           #+#    #+#             */
/*   Updated: 2025/07/12 12:47:38 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// get the current time in milliseconds
long	get_current_time(void)
{
	long			start_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}

//get the timestamp since the start of the simulation
long	timestamp(long start_time)
{
	long			current_time;
	long			timestamp;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	timestamp = current_time - start_time;
	return (timestamp);
}

//calculates the time passed since the last meal eaten
long	time_since_meal(long last_meal)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time - last_meal);
}

void	sleep_v2(t_philo *philo, long time)
{
	long	start;

	start = get_current_time();
	while (1)
	{
		if (check_sim_over(philo) == 1)
			return ;
		if (get_current_time() - start >= time)
			return ;
		usleep(500);
	}
}
