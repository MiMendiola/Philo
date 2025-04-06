/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:26 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/06 14:49:30 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int show_error(char *error)
{
    printf(RED"%s\n"CLEAR , error);
    return (1);
}

void print_table(struct s_table *table)
{
    if (!table)
    {
        printf("Error: Table is NULL\n");
        return;
    }
    printf("Philosopher Count: %d\n", table->philo_nbr);
    printf("Time to Die (ms): %ld\n", table->timeToDieMs);
    printf("Time to Eat (ms): %ld\n", table->timeToEatMs);
    printf("Time to Sleep (ms): %ld\n", table->timeToSleepMs);
    printf("Max Times Eaten: %d\n", table->mealsToDo);

    /*if (table->philos)
    {
        printf("\nPhilosopher Data:\n");
        for (int i = 0; i < table->philo_nbr; i++)
        {
            printf("  Philosopher %d:\n", i + 1);
            // Aquí puedes imprimir los datos de `t_philo` según su estructura
        }
    }
    else
        printf("No philosophers data available.\n");*/
}

int main(int ac, char *av[])
{
    t_table *table;
    
    table = ft_calloc(1, sizeof(t_table));
    if (!table)
        return (show_error("Memory allocation failed"));
        
    if (ac != 5 && ac != 6)
        return (show_error("Incorrect usage. Please, correct the input."));
    
    if (create_table(table, av))
        return (free(table), 1);
    
    init_data(table);
    simulation_start(table);
    clean_table(table);
    /* Creamos tenedores */

    /* Creamos las estructuras de los philosofos */

    /* Crear hilo monitor */

    /* [Creamos os hilos de los filosofos y el monitor => Empiezan a la vez] <= Es necesario que empeicen a la vez (sincronización) */

    /* ROUTINE y MONITOR_ROUTINE */

    /* Liberar memoria - Eliminar todos */

    return (0);
}


// for (int i = 0; i < philo_count; i++)
//     pthead_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
// pthead_create(&monitor_thread, NULL, monitor_routine, &gloabl_data)
