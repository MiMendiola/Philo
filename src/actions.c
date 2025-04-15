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
