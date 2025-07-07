#include "../include/philo.h"

void	*test_thread(void *arg)
{
	t_mutex *data_mutex;

	data_mutex = (t_mutex *)arg; //cast the arg from void to our structure
	pthread_mutex_lock(data_mutex->mutex); //lock mutex
	data_mutex->thread_num = 2; //change the datas value
	printf("test thread: %d\n", data_mutex->thread_num); //print it
	pthread_mutex_unlock(data_mutex->mutex); //unlock mutex
	return (NULL);
}

void	*test_thread2(void *arg)
{
	t_mutex *data_mutex;

	data_mutex = (t_mutex *)arg; //cast the arg from void to our structure
	pthread_mutex_lock(data_mutex->mutex); //lock mutex
	data_mutex->thread_num = 3; //change the datas value
	printf("test thread: %d\n", data_mutex->thread_num); //print it
	pthread_mutex_unlock(data_mutex->mutex); //unlock mutex
	return (NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	data;
	pthread_t t1;
	pthread_t t2;
	pthread_mutex_t lock;
	t_mutex	data_mutex;

	pthread_mutex_init(&lock, NULL); // init mutex

	data_mutex.mutex = &lock; //set values of the data structure
	data_mutex.thread_num = 1;
	// INIT
	init_data(&data);

	// PARSING
	data.er_code = parser(ac, av, &data);
	if (data.er_code != 0)
		return (print_err(data.er_code));
		
	pthread_create(&t1, NULL, test_thread, &data_mutex); //create threads
	pthread_create(&t2, NULL, test_thread2, &data_mutex);

	pthread_join(t1, NULL); //wait for threads to finish before exiting program
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock); // destroy mutex
	return (0);
}