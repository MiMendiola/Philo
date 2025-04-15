#include "../includes/philo.h"

bool    simulation_finish(t_table *table)
{
    return (get_bool(&table->mutex_table, &table->endSimulation));
}

void    *simulation_dinner(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    threads_waiter(philo->table);

    set_long(&philo->mutex, &philo->lastMeal, get_time(MILLISECONDS));

    increase_long(&philo->table->mutex_table, &philo->table->threadsRunning);

    syncronizing_philos(philo);

    while (!simulation_finish(philo->table))
    {
        if (philo->full)
            break ;
        
        eat(philo);

        write_status(philo, SLEEPS, DEBUG_MODE);
        precise_usleep(philo->table->timeToSleepMs, philo->table);

        thinking(philo, false);
    }
    return (NULL);
}

void    *simulation_monitor(void *data)
{
    int i;
    t_table *table;

    table = (t_table *)data;

    while (!threads_running(&table->mutex_table, &table->threadsRunning, table->philo_nbr))
        usleep(100);

    while(!simulation_finish(table))
    {
        i = 0;
        while (table->philo_nbr > i && !simulation_finish(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->mutex_table, &table->endSimulation, true);
                write_status(table->philos, DIED, DEBUG_MODE);
            }
            i++;
        }
    }
    return (NULL);
}

void    *alone_philo(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    threads_waiter(philo->table);
    set_long(&philo->mutex, &philo->lastMeal, get_time(MILLISECONDS));
    increase_long(&philo->table->mutex_table, &philo->table->threadsRunning);
    write_status(philo, TAKE_LEFT_FORK, DEBUG_MODE);
    while (!simulation_finish(philo->table))
        usleep(200);
    return (NULL);
}

void    simulation_start(t_table *table)
{
    int i;

    i = 0;
    if (table->philo_nbr == 0)
        return ;
    table->startSimulation = get_time(MILLISECONDS);
    if (table->philo_nbr == 1)
        thread_handler(&table->philos[0].threadId, alone_philo, &table->philos[0], CREATE);
    else
    {
        while (table->philo_nbr > i)
        {
            thread_handler(&table->philos[i].threadId, simulation_dinner, &table->philos[i], CREATE);
            i++;
        }
    }
    thread_handler(&table->monitor, simulation_monitor, table, CREATE);
    set_bool(&table->mutex_table, &table->threadsReady, true);
    i = 0;
    while (table->philo_nbr > i)
    {
        thread_handler(&table->philos[i].threadId, NULL, NULL, JOIN);
        i++;
    }
    set_bool(&table->mutex_table, &table->endSimulation, true);
    thread_handler(&table->monitor, NULL, NULL, JOIN);
}
