#include "../includes/philo.h"

void    mutex_error_handler(int status, t_opscode code)
{
    if (status == 0)
        return ;
    if (status == EINVAL)
}

void    mutex_handler(pthread_mutex_t *mutex, t_opscode code)
{
    if (code == LOCK)
}