#include "../includes/philo.h"

void    assign_forks(t_philo *philo, t_fork *forks, int philoPosition)
{
    int total_philos;

    total_philos = philo->table->philo_nbr;
    if (total_philos == 1)
    {
        philo->leftFork = &forks[0];
        philo->rightFork = NULL;
        return;
    }

    philo->leftFork = &forks[(philoPosition + 1) % total_philos];
    philo->rightFork = &forks[philoPosition];
    if (philo->id % 2 == 0)
    {
        philo->leftFork = &forks[philoPosition];
        philo->rightFork = &forks[(philoPosition + 1) % total_philos];
    }
}

void    init_philo(t_table *table)
{
    int i;
    t_philo *philo;

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

void    init_data(t_table *table)
{
    int i;

    i = 0;
    table->endSimulation = false;
    table->threadsReady = false;
    table->threadsRunning = 0;
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