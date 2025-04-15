#include "../includes/philo.h"

void    increase_long(pthread_mutex_t *mutex, long *value)
{
    mutex_handler(mutex, LOCK);
    (*value)++;
    mutex_handler(mutex, UNLOCK);
}

void    syncronizing_philos(t_philo *philo)
{
    if (philo->table->philo_nbr % 2 == 0)
    {
        if (philo->id % 2 == 0)
            precise_usleep(3000, philo->table);
    }
    else
    {
        if (philo->id % 2)
            thinking(philo, true);
    }
}

void    threads_waiter(t_table *table)
{
    while (!get_bool(&table->mutex_table, &table->threadsReady))
        return ;
}

bool    threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool    res;

    res = false;
    mutex_handler(mutex, LOCK);
    if (*threads == philo_nbr)
        res = true;
    mutex_handler(mutex, UNLOCK);
    return (res);
}

bool    philo_died(t_philo *philo)
{
    long    elapsed;
    long    time_die;
    
    if (get_bool(&philo->mutex, &philo->full))
        return (false);
    elapsed = get_time(MILLISECONDS) - get_long(&philo->mutex, &philo->lastMeal);
    time_die = philo->table->timeToDieMs / 1000;

    return (elapsed >= time_die);
}
