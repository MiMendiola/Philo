/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:01:44 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/06 14:57:05 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(t_times time_code)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (show_error("EXIT ERROR TO SOLVE"), -1);
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		return (show_error("EXIT ERROR TO SOLVE"), -1);
	return (-99);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < usec)
	{
		if (simulation_finish(table))
			break ;
		elapsed = get_time(MICROSECONDS);
		rem = usec - elapsed;

		if (rem > 1000)
			usleep(rem / 2);
		else
			while (get_time(MICROSECONDS) - start < usec)
				;
	}
	
}


void	write_status_debug(t_philo *philo, t_status_philo status, long elapsed)
{
	if (status == TAKE_LEFT_FORK && !simulation_finish(philo->table))
		printf("%-5ld %d has taken the left fork -> %d\n", elapsed, philo->id, philo->leftFork->id);
	else if (status == TAKE_RIGHT_FORK && !simulation_finish(philo->table))
		printf("%-5ld %d has taken the right fork -> %d\n", elapsed, philo->id, philo->rightFork->id);
	else if (status == EATS && !simulation_finish(philo->table))
		printf("%-5ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPS && !simulation_finish(philo->table))
		printf("%-5ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKS && !simulation_finish(philo->table))
		printf("%-5ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-5ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo *philo, t_status_philo status, bool debug)
{
	long	elapsed;
	
	elapsed = get_time(MILLISECONDS) - philo->table->startSimulation;
	
	if (philo->full)
		return ;
	
	mutex_handler(&philo->table->mutex_write, LOCK);
	if (debug)
		write_status_debug(philo, status, elapsed);
	else
	{
		if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK) && !simulation_finish(philo->table))
			printf("%-5ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATS && !simulation_finish(philo->table))
			printf("%-5ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPS && !simulation_finish(philo->table))
			printf("%-5ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKS && !simulation_finish(philo->table))
			printf("%-5ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-5ld %d died\n", elapsed, philo->id);
	}
	
	mutex_handler(&philo->table->mutex_write, UNLOCK);
}




















/* 

void	free_list(t_philo **stack)
{
	t_philo	*aux;

	while (*stack)
	{
		aux = (*stack)->next;
		pthread_mutex_destroy(&aux->lock);
		free(*stack);
		*stack = aux;
	}
	free(stack);
}

t_philo	*last_node(t_philo *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*new_node(int id, char *av[])
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
//	pthread_mutex_init(&philo->lock, NULL);
	philo->prev = NULL;
	philo->next = NULL;
	philo->timeToDieMs = ft_atoi(av[2]);
	philo->timeToEatMs = ft_atoi(av[3]);
	philo->timeToSleepMs = ft_atoi(av[4]);
	if (av[5])
		philo->maxTimesEaten = ft_atoi(av[5]);
	else
		philo->maxTimesEaten = INT_MAX;
	if ((philo->timeToDieMs == INT_MAX + 1) || (philo->timeToEatMs == INT_MAX + 1) || (philo->timeToSleepMs == INT_MAX + 1) || (philo->maxTimesEaten == INT_MAX + 1))
		return(free(philo), NULL);
	return (philo);
}

void	add_node_back(t_philo **stack, t_philo *new)
{
	t_philo	*aux;

	aux = last_node(*stack);
	if (*stack != NULL)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
}
 */
