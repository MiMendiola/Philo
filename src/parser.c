#include "../includes/philo.h"

long	parse_arguments(char *str)
{
    long n = 0;
    int i = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+' || str[i] == '-')
        if (str[i++] == '-') 
            return (show_error("Only positive numbers allowed"), -1);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (show_error("Only numbers allowed"), -1);
        n = n * 10 + (str[i++] - '0');
        if (n > INT_MAX)
            return (show_error("Number is too big"), -1);
    }
    return (n);
}

int    create_table(t_table *table, char *av[])
{
    table->philo_nbr = parse_arguments(av[1]);
    table->timeToDieMs = parse_arguments(av[2]) * 1000;
    table->timeToEatMs = parse_arguments(av[3]) * 1000;
    table->timeToSleepMs = parse_arguments(av[4]) * 1000;
    if (av[5])
        table->maxTimesEaten = parse_arguments(av[5]);
    else
        table->maxTimesEaten = -9;
    if (table->philo_nbr < 1 || table->timeToDieMs < 1 || table->timeToEatMs < 1 || table->timeToSleepMs < 1 || table->maxTimesEaten == -1)
        return (1);
    return (0);
}









