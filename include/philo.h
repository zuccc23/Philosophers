/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:49:34 by dahmane           #+#    #+#             */
/*   Updated: 2025/07/12 13:11:20 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

//structure of 1 philosopher
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_time;
	pthread_mutex_t	meal_count;
	struct s_data	*data;
}	t_philo;

//stucture of overall data
typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				simulation_over;
	int				er_code;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		*threads;
	t_philo			*philos;
}	t_data;

// MAIN ///////////////////////////////////////

int		check_single_philo(t_data data);
void	end_program(t_data	*data);
void	threads_loop(t_data *data);
void	join_loop(t_data *data);

// INIT ///////////////////////////////////////

void	init_data(t_data *data);
void	init_philos(t_data *data);
void	init_mutexes(t_data *data);
void	init_mut_and_philos(t_data *data);
int		allocate_data(t_data *data);

// PARSING ////////////////////////////////////

int		parser(int ac, char **av, t_data *data);
int		get_args(char **av, t_data *data);

// ROUTINE ////////////////////////////////////

void	*philo_routine(void *arg);
void	pickup_forks(t_philo *philo);
void	eat(t_philo *philo);
void	putdown_forks(t_philo *philo);

// ROUTINE UTILS //////////////////////////////

void	print_state(t_philo *philo, int state);
int		is_even(int n);
int		check_sim_over(t_philo *philo);

// UTILS //////////////////////////////////////

int		ft_isdigit(int c);
int		ft_is_number(char *str);
size_t	ft_strlen(const char *str);
long	ft_atoll(const char *str);
void	ft_putsterr(char *s);

// TIME UTILS /////////////////////////////////

long	get_current_time(void);
long	timestamp(long start_time);
long	time_since_meal(long last_meal);
void	sleep_v2(t_philo *philo, long time);

// SIMULATION OVER ////////////////////////////

void	check_end(t_data *data);
int		check_death(t_data *data, int i);
int		check_meals_eaten(t_data *data);

// ERRORS

int		print_err(int er_code);

// FREE ////////////////////////////////////////

void	destroy_mutexes(t_data *data);

// MACROS //////////////////////////////////////

# define NON_NUMERIC 1
# define TOO_LONG 2
# define NUMBER_TOO_SMALL 3
# define TOO_FEW_ARGS 4

typedef enum t_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_state;

#endif