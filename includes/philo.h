/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/28 13:25:38 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <errno.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_table	t_table;

typedef enum	e_actions
{
    DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKING_A_FORK
}		t_actions;

typedef enum	e_opscode
{
    LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}		t_opscode;

struct  s_fork
{
    int				id;
	pthread_mutex_t	fork;
};

struct  s_philo
{
    int				id;
	pthread_t		thread;
	pthread_mutex_t	lock;
	t_philo			*prev;
	t_philo			*next;
};

struct	s_table
{
	int			philo_nbr;
	long		timeToDieMs;
	long		timeToEatMs;
	long		timeToSleepMs;
	int			maxTimesEaten;
	int			end_philo;
	t_fork		*forks;
	t_philo		*philos;
};


/* ======================================= */
/*			   SETTINGS COLORS			   */
/* ======================================= */
#define BLACK "\x1B[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1B[37m"
#define ORANGE "\x1B[38;2;255;128;0m"
#define ROSE "\x1B[38;2;255;151;203m"
#define LBLUE "\x1B[38;2;53;149;240m"
#define LGREEN "\x1B[38;2;17;245;120m"
#define GRAY "\x1B[38;2;176;174;174m"
#define CLEAR "\x1b[0m"

/*===========================================*/
/*                    ALGO                 	 */
/*===========================================*/
int show_error(char *error);

//  PARSER
long	parse_arguments(char *str);
int		create_table(t_table *table, char *av[]);

//	HANDLERS
void    mutex_error_handler(int status, t_opscode code);
void    mutex_handler(pthread_mutex_t *mutex, t_opscode code);
void    thread_error_handler(int status, t_opscode code);
void    thread_handler(pthread_t *thread, void *(*foo)(void *), void *data, t_opscode code);

//	PHILO_UTILS
void	free_list(t_philo **stack);
t_philo	*last_node(t_philo *lst);
t_philo	*new_node(int id, char *av[]);
void	add_node_back(t_philo **stack, t_philo *new);

//	PHILO_LIB
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int c);

#endif