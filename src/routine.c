#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_sim_over(philo) == 0)
	{
		pickup_forks(philo);
		eat(philo);
		putdown_forks(philo);
		if (check_sim_over(philo) == 0)
		{
			print_state(philo, SLEEP);
			sleep_v2(philo, philo->data->time_to_sleep);
			if (check_sim_over(philo) == 0)
				print_state(philo, THINK);
		}
	}
	return (NULL);
}

void	pickup_forks(t_philo *philo)
{
	if (check_sim_over(philo) == 1)
		return ;
	if (is_even(philo->id) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, FORK);
	}
	if (is_even(philo->id) == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, FORK);
	}
}

void	eat(t_philo *philo)
{
	if (check_sim_over(philo) == 1)
		return ;
	print_state(philo, EAT);
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_time);
	sleep_v2(philo, philo->data->time_to_eat);
}

void	putdown_forks(t_philo *philo)
{
	if (is_even(philo->id) == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
