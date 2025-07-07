#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

//structure of 1 philosopher
typedef struct s_philo {
	int id;                    // Philosopher number (1 to N)
	int meals_eaten;           // Number of meals eaten
	long last_meal_time;       // Timestamp of last meal
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_data *data;       // Pointer to shared data
} t_philo;

typedef struct s_mutex {
	pthread_mutex_t* mutex;
    int thread_num;
} t_mutex;

//stucture of overall data
typedef struct s_data {
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;        // Optional argument
	long start_time;
	int simulation_over;
	int er_code;
	pthread_mutex_t *forks;    // Array of fork mutexes
	pthread_mutex_t print_mutex;
	pthread_mutex_t death_mutex;
	pthread_t *threads;
	t_philo *philosophers;
} t_data;

// INIT ///////////////////////////////////////

void	init_data(t_data *data);

// PARSING ////////////////////////////////////

int		parser(int ac, char **av, t_data *data);
int		get_args(char **av, t_data *data);

// UTILS //////////////////////////////////////

int		ft_isdigit(int c);
int		ft_is_number(char *str);
size_t	ft_strlen(const char *str);
long	ft_atoll(const char *str);
void	ft_putsterr(char *s);

// ERRORS

int		print_err(int er_code);

// MACROS //////////////////////////////////////

# define NON_NUMERIC 1
# define TOO_LONG 2
# define NUMBER_TOO_SMALL 3
# define TOO_FEW_ARGS 4

#endif