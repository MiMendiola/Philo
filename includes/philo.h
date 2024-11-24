/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2024/11/24 12:24:02 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

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


/*===========================================*/
/*                ALGO                  */
/*===========================================*/
//  ALGO.C

#endif