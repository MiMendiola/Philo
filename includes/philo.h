/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2025/04/22 15:36:28 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DEBUG_MODE 0

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_table	t_table;

typedef enum e_status_philo
{
	EATS,
	SLEEPS,
	THINKS,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED
}						t_status_philo;

typedef enum e_times
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}						t_times;

typedef enum e_actions
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKING_A_FORK
}						t_actions;

typedef enum e_opscode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opscode;

struct					s_fork
{
	int					id;
	pthread_mutex_t		fork;
};

struct					s_philo
{
	int					id;
	pthread_t			thread_id;
	int					meals;
	bool				full;
	long				last_meal;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		mutex;
	t_table				*table;
};

struct					s_table
{
	int					philo_nbr;
	long				time_to_die_ms;
	long				time_to_eat_ms;
	long				time_to_sleep_ms;
	int					meals_todo;
	long				start_simulation;
	bool				end_simulation;
	bool				threads_ready;
	long				threads_running;
	pthread_t			monitor;
	pthread_mutex_t		mutex_table;
	pthread_mutex_t		mutex_write;
	t_fork				*forks;
	t_philo				*philos;
};

/* ======================================= */
/*				SETTINGS COLORS			   */
/* ======================================= */
# define BLACK "\x1B[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1B[37m"
# define ORANGE "\x1B[38;2;255;128;0m"
# define ROSE "\x1B[38;2;255;151;203m"
# define LBLUE "\x1B[38;2;53;149;240m"
# define LGREEN "\x1B[38;2;17;245;120m"
# define GRAY "\x1B[38;2;176;174;174m"
# define CLEAR "\x1b[0m"

/*===========================================*/
/*                    ALGO                 		*/
/*===========================================*/
int						show_error(char *error);

//	ACTIONS
void					thinking(t_philo *philo, bool presimulation);
void					eat(t_philo *philo);

//	GETTERS_SETTERS
void					set_bool(pthread_mutex_t *mutex, bool *dst, bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
void					set_long(pthread_mutex_t *mutex, long *dst, long value);
long					get_long(pthread_mutex_t *mutex, long *value);

//	HANDLERS
void					mutex_error_handler(int status, t_opscode code);
void					mutex_handler(pthread_mutex_t *mutex, t_opscode code);
void					thread_error_handler(int status, t_opscode code);
void					thread_handler(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opscode code);

//  INIT
void					assign_forks(t_philo *philo, t_fork *forks,
							int philoPosition);
void					init_philo(t_table *table);
void					init_data(t_table *table);
int						init_table(t_table *table, char *av[]);

//	PHILO_LIB
void					*ft_memset(void *str, int value, size_t len);
void					ft_bzero(void *str, size_t len);
void					*ft_calloc(size_t count, size_t size);
int						ft_isdigit(int c);

//	PHILO_UTILS
long					parse_arguments(char *str);
long					get_time(t_times time_code);
void					precise_usleep(long usec, t_table *table);
void					write_status_debug(t_philo *philo,
							t_status_philo status, long elapsed);
void					write_status(t_philo *philo, t_status_philo status,
							bool debug);

//	SIMULATION
bool					simulation_finish(t_table *table);
void					*simulation_dinner(void *data);
void					*simulation_monitor(void *data);
void					*alone_philo(void *data);
void					simulation_start(t_table *table);

//	SYNCRO
void					increase_long(pthread_mutex_t *mutex, long *value);
void					syncronizing_philos(t_philo *philo);
void					threads_waiter(t_table *table);
bool					threads_running(pthread_mutex_t *mutex, long *threads,
							long philo_nbr);
bool					philo_died(t_philo *philo);

#endif