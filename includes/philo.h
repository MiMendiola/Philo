/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/03 11:28:51 by lmntrix          ###   ########.fr       */
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

typedef struct s_philo	t_philo;
enum                    e_actions;

enum    e_actions
{
    DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKING_A_FORK
};

struct  s_philo
{
    int				id;
	pthread_t		thread;
	pthread_mutex_t	lock;
	t_philo			*prev;
	t_philo			*next;
	long			timeToDieMs;
	long			timeToEatMs;
	long			timeToSleepMs;
	int				maxTimesEaten;
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
//  ALGO.C
long	atol_philo(char *str);


#endif