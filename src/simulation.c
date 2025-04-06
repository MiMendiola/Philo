#include "../includes/philo.h"

void    thinking(t_philo *philo, bool presimulation)
{
    long    time_eat;
    long    time_sleep;
    long    time_think;

    if (!presimulation)
        write_status(philo, THINKS, DEBUG_MODE);
    
    if (philo->table->philo_nbr % 2 == 0)
        return ;

    time_eat = philo->table->timeToEatMs;
    time_sleep = philo->table->timeToSleepMs;
    time_think = time_eat * 2 - time_sleep;
    
    if (time_think < 0)
        time_think = 0;

    precise_usleep(time_think, philo->table);
}

void    eat(t_philo *philo)
{
    mutex_handler(&philo->leftFork->fork, LOCK);
    write_status(philo, TAKE_LEFT_FORK, DEBUG_MODE);
    mutex_handler(&philo->rightFork->fork, LOCK);
    write_status(philo, TAKE_RIGHT_FORK, DEBUG_MODE);

    set_long(&philo->mutex, &philo->lastMeal, get_time(MILLISECONDS));
    philo->meals++;
    write_status(philo, EATS, DEBUG_MODE);
    precise_usleep(philo->table->timeToEatMs, philo->table);
    if (philo->table->mealsToDo > 0 && philo->meals == philo->table->mealsToDo)
        set_bool(&philo->mutex, &philo->full, true);

    mutex_handler(&philo->leftFork->fork, UNLOCK);
    mutex_handler(&philo->rightFork->fork, UNLOCK);
}


bool    simulation_finish(t_table *table)
{
    return (get_bool(&table->mutex_table, &table->endSimulation));
}

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

    return (elapsed > time_die);
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

void    clean_table(t_table *table)
{
    int i;
    t_philo *philo;

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