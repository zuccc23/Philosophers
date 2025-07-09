#include "../include/philo.h"

void	print_state(t_philo *philo, int state)
{
	long	time;

	
	time = timestamp(philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (state == FORK)
		printf("{%ld} philo[%d] has taken a fork\n", time, philo->id);
	if (state == EAT)
		printf("\033[0;32m{%ld} philo[%d] is eating\033[0m\n", time, philo->id);
	if (state == SLEEP)
		printf("{%ld} philo[%d] is sleeping\n", time, philo->id);
	if (state == THINK)
		printf("{%ld} philo[%d] is thinking\n", time, philo->id);
	if (state == DIE)
		printf("\033[0;31m{%ld} philo[%d] died\033[0m\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// returns 0 if n is an even number
//return 1 if its an odd number
int	is_even(int n)
{
	if (n % 2 == 0)
		return (0);
	return (1);
}