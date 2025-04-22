/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:16 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/22 15:37:53 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->mutex_table, &table->end_simulation));
}

void	*simulation_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	threads_waiter(philo->table);
	set_long(&philo->mutex, &philo->last_meal, get_time(MILLISECONDS));
	increase_long(&philo->table->mutex_table, &philo->table->threads_running);
	syncronizing_philos(philo);
	while (!simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(philo, SLEEPS, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep_ms, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	*simulation_monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(&table->mutex_table, &table->threads_running,
			table->philo_nbr))
		usleep(100);
	while (!simulation_finish(table))
	{
		i = 0;
		while (table->philo_nbr > i && !simulation_finish(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->mutex_table, &table->end_simulation, true);
				write_status(table->philos, DIED, DEBUG_MODE);
			}
			i++;
		}
	}
	return (NULL);
}

void	*alone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	threads_waiter(philo->table);
	set_long(&philo->mutex, &philo->last_meal, get_time(MILLISECONDS));
	increase_long(&philo->table->mutex_table, &philo->table->threads_running);
	write_status(philo, TAKE_LEFT_FORK, DEBUG_MODE);
	while (!simulation_finish(philo->table))
		usleep(200);
	return (NULL);
}

void	simulation_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo_nbr == 0)
		return ;
	table->start_simulation = get_time(MILLISECONDS);
	if (table->philo_nbr == 1)
		thread_handler(&table->philos[0].thread_id, alone_philo,
			&table->philos[0], CREATE);
	else
	{
		while (table->philo_nbr > ++i)
			thread_handler(&table->philos[i].thread_id, simulation_dinner,
				&table->philos[i], CREATE);
	}
	thread_handler(&table->monitor, simulation_monitor, table, CREATE);
	set_bool(&table->mutex_table, &table->threads_ready, true);
	i = -1;
	while (table->philo_nbr > ++i)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->mutex_table, &table->end_simulation, true);
	thread_handler(&table->monitor, NULL, NULL, JOIN);
}
