/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:26 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/22 15:35:44 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	show_error(char *error)
{
	printf(RED "%s\n" CLEAR, error);
	return (1);
}

void	print_table(struct s_table *table)
{
	if (!table)
	{
		printf("Error: Table is NULL\n");
		return ;
	}
	printf("Philosopher Count: %d\n", table->philo_nbr);
	printf("Time to Die (ms): %ld\n", table->time_to_die_ms);
	printf("Time to Eat (ms): %ld\n", table->time_to_eat_ms);
	printf("Time to Sleep (ms): %ld\n", table->time_to_sleep_ms);
	printf("Max Times Eaten: %d\n", table->meals_todo);
}

void	clean_table(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (table->philo_nbr > i)
	{
		philo = table->philos + i;
		mutex_handler(&philo->mutex, DESTROY);
		i++;
	}
	mutex_handler(&table->mutex_write, DESTROY);
	mutex_handler(&table->mutex_table, DESTROY);
	free(table->forks);
	free(table->philos);
}

int	main(int ac, char *av[])
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (show_error("Memory allocation failed"));
	if (ac != 5 && ac != 6)
		return (show_error("Incorrect usage. Please, correct the input."));
	if (init_table(table, av))
		return (free(table), 1);
	init_data(table);
	simulation_start(table);
	clean_table(table);
	return (0);
}
