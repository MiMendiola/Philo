/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:21:00 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/22 15:37:06 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo, bool presimulation)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!presimulation)
		write_status(philo, THINKS, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	time_eat = philo->table->time_to_eat_ms;
	time_sleep = philo->table->time_to_sleep_ms;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	precise_usleep(time_think, philo->table);
}

void	eat(t_philo *philo)
{
	mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(philo, TAKE_LEFT_FORK, DEBUG_MODE);
	mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(philo, TAKE_RIGHT_FORK, DEBUG_MODE);
	set_long(&philo->mutex, &philo->last_meal, get_time(MILLISECONDS));
	philo->meals++;
	write_status(philo, EATS, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat_ms, philo->table);
	if (philo->table->meals_todo > 0
		&& philo->meals == philo->table->meals_todo)
		set_bool(&philo->mutex, &philo->full, true);
	mutex_handler(&philo->left_fork->fork, UNLOCK);
	mutex_handler(&philo->right_fork->fork, UNLOCK);
}
