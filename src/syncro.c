#include "../includes/philo.h"

void    threads_waiter(t_table *table)
{
    while (!get_bool(&table->mutex_table, &table->threadsReady))
        return ;
}