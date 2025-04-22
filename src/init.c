/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:05 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/22 15:36:44 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int philoPosition)
{
	int	total_philos;

	total_philos = philo->table->philo_nbr;
	if (total_philos == 1)
	{
		philo->left_fork = &forks[0];
		philo->right_fork = NULL;
		return ;
	}
	philo->left_fork = &forks[(philoPosition + 1) % total_philos];
	philo->right_fork = &forks[philoPosition];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[philoPosition];
		philo->right_fork = &forks[(philoPosition + 1) % total_philos];
	}
}

void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (table->philo_nbr > i)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		mutex_handler(&philo->mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->threads_ready = false;
	table->threads_running = 0;
	table->philos = ft_calloc(table->philo_nbr, sizeof(t_philo));
	mutex_handler(&table->mutex_table, INIT);
	table->forks = ft_calloc(table->philo_nbr, sizeof(t_fork));
	while (table->philo_nbr > i)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].id = 0;
		i++;
	}
	init_philo(table);
}

int	init_table(t_table *table, char *av[])
{
	table->philo_nbr = parse_arguments(av[1]);
	table->time_to_die_ms = parse_arguments(av[2]) * 1000;
	table->time_to_eat_ms = parse_arguments(av[3]) * 1000;
	table->time_to_sleep_ms = parse_arguments(av[4]) * 1000;
	if (av[5])
		table->meals_todo = parse_arguments(av[5]);
	else
		table->meals_todo = -9;
	if (table->philo_nbr < 1 || table->time_to_die_ms < 1
		|| table->time_to_eat_ms < 1 || table->time_to_sleep_ms < 1
		|| table->meals_todo == -1)
		return (1);
	return (0);
}
