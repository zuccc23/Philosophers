#include "../include/philo.h"

// get the start time of the simulation
long	get_start_time(void)
{
	long	start_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}

//get the timestamp since the start of the simulation
long	timestamp(long start_time)
{
	long	current_time;
	long	timestamp;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	timestamp = current_time - start_time;
	return (timestamp);
}

// tv.tv_sec * 1000 + tv.tv_usec / 1000