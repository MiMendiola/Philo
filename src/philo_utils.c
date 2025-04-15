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

long	parse_arguments(char *str)
{
    long n = 0;
    int i = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+' || str[i] == '-')
        if (str[i++] == '-') 
            return (show_error("Only positive numbers allowed"), -1);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (show_error("Only numbers allowed"), -1);
        n = n * 10 + (str[i++] - '0');
        if (n > INT_MAX)
            return (show_error("Number is too big"), -1);
    }
    return (n);
}

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
