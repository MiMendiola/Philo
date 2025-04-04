#include "../includes/philo.h"

void    init_data(t_table *table)
{
    int i;

    i = 0;
    table->end_philo = 0;
    table->philos = ft_calloc(table->philo_nbr, sizeof(t_philo));
    table->forks = ft_calloc(table->philo_nbr, sizeof(t_fork));
    while (table->philo_nbr > i)
    {
        mutex_error_handler(&table->forks[i].fork, INIT);
        table->forks[i].id = 0;
        i++;
    }
    init_philo(table);
}